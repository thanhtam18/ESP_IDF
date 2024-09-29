#include "dev_http_server.h"
#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>
#include <sys/param.h>
#include "esp_netif.h"
#include "esp_eth.h"
#include <esp_http_server.h>
// embedded image
// extern const uint8_t anh_start[] asm("_binary_doraemon1_jpeg_start");
// extern const uint8_t anh_end[] asm("_binary_doraemon1_jpeg_end");
// embedded html
extern const uint8_t html_start[] asm("_binary_webserver_html_start");
extern const uint8_t html_end[] asm("_binary_webserver_html_end");
static httpd_handle_t server = NULL;
static const char *TAG = "HTTP";


static http_wifi_callback_t http_wifi_callback = NULL;


/* An HTTP GET handler */
static esp_err_t web_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, (const char *)html_start, html_end - html_start);
    return ESP_OK;
}

static esp_err_t wifi_handler(httpd_req_t *req)
{
    char buf[100];
    httpd_req_recv(req, buf, req->content_len);
    http_wifi_callback(buf, req->content_len);
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

static const httpd_uri_t wifiinfor = {
    .uri = "/post",
    .method = HTTP_POST,
    .handler = wifi_handler,
    .user_ctx = NULL};

static const httpd_uri_t web = {
    .uri = "/index",
    .method = HTTP_GET,
    .handler = web_handler,
    .user_ctx = NULL};

esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err)
{
    if (strcmp("/post", req->uri) == 0)
    {
        httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "/post URI is not available");
        /* Return ESP_OK to keep underlying socket open */
        return ESP_OK;
    }
    /* For any other URI send 404 and close socket */
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Some 404 error message");
    return ESP_FAIL;
}

void start_webserver(void)
{

    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK)
    {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &wifiinfor);
        httpd_register_uri_handler(server, &web);
        httpd_register_err_handler(server, HTTPD_404_NOT_FOUND, http_404_error_handler);
    }
    else
    {
        ESP_LOGI(TAG, "Error starting server!");
    }
}

void stop_webserver(void)
{
    // Stop the httpd server
    httpd_stop(server);
}

void http_set_wifi_callback(void *cb)
{
    http_wifi_callback = cb;
}
