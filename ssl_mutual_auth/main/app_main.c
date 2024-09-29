/* MQTT Mutual Authentication Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"
#include "dev_app_config.h"
#include "app_mqtt.h"
#include "app_nvs.h"

#define KEY "Restart counter"
#define KEY1 "String"
static const char *TAG = "Sonoff";



void app_main(void)
{
    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    int inc_start = 0;
    app_nvs_get_value(KEY, &inc_start);
    inc_start ++;
    app_nvs_set_value(KEY,inc_start);
    char string1[50];
    sprintf(string1,"Hello %d",inc_start);
    char string2[50];
    app_nvs_get_str(KEY1,string2);
    app_nvs_set_str(KEY1,string1);

    //dev_config_wifi();
   // mqtt_app_init();
   // mqtt_app_start();
}
