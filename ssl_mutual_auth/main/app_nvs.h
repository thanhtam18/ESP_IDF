#ifndef _DEV_NVS_H
#define _DEV_NVS_H

void app_nvs_get_value(char *key, int *value);
void app_nvs_set_value(char *key, int value);
void app_nvs_get_str(char *key, char * out);
void app_nvs_set_str(char *key, char *str);

#endif