#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "app_nvs.h"

#define USER_NAMESPACE "Stored"
nvs_handle_t my_handle;

void app_nvs_get_value(char *key, int *value)
{
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS) handle... ");
    int err = nvs_open(USER_NAMESPACE, NVS_READWRITE, &my_handle);
    if (err != ESP_OK)
    {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    }
    else
    {
        printf("Done\n");
        printf("Reading %s from NVS ... ",key);
        err = nvs_get_i32(my_handle, key, value);
        switch (err)
        {
        case ESP_OK:
            printf("Done\n");
            printf("%s = %d\n",key, *value);
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            printf("The %s is not initialized yet!\n",key);
            break;
        default:
            printf("Error (%s) reading!\n", esp_err_to_name(err));
        }
    }
    nvs_close(my_handle);
    printf("\n");
}

void app_nvs_set_value(char *key, int value)
{
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS) handle... ");
    int err = nvs_open(USER_NAMESPACE, NVS_READWRITE, &my_handle);
    if (err != ESP_OK)
    {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    }
    else
    {
        printf("Done\n");
        printf("Updating %s in NVS ... ",key);
        err = nvs_set_i32(my_handle, key, value);
        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
        printf("Committing updates in NVS ... ");
        err = nvs_commit(my_handle);
        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
        nvs_close(my_handle);
    }
    printf("\n");
}

void app_nvs_set_str(char *key, char *str)
{
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS) handle... ");
    int err = nvs_open(USER_NAMESPACE, NVS_READWRITE, &my_handle);
    if (err != ESP_OK)
    {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    }
    else
    {
        printf("Done\n");
        printf("Updating %s in NVS ... ",key);
        err = nvs_set_str(my_handle, key, str);
        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
        printf("Committing updates in NVS ... ");
        err = nvs_commit(my_handle);
        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
        nvs_close(my_handle);
    }
    printf("\n");
}

void app_nvs_get_str(char *key, char * out)
{
    size_t len = 0;
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS) handle... ");
    int err = nvs_open(USER_NAMESPACE, NVS_READWRITE, &my_handle);
    if (err != ESP_OK)
    {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    }
    else
    {
        printf("Done\n");
        printf("Reading %s from NVS ... ",key);
        err = nvs_get_str(my_handle, key, out, &len);
        err = 0;
        err = nvs_get_str(my_handle, key, out, &len);
        switch (err)
        {
        case ESP_OK:
            printf("Done\n");
            printf("%s = %s, length = %d\n", key, out, len);
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            printf("The %s is not initialized yet!\n",key);
            break;
        default:
            printf("Error (%s) reading!\n", esp_err_to_name(err));
        }
    }
    nvs_close(my_handle);
    printf("\n");
}