#ifndef _DEV_SMART_CONFIG_H
#define _DEV_SMART_CONFIG_H

typedef enum
{
    PROVISION_SMARTCONFIG = 0,
    PROVISION_ACCESSPOINT = 1
}  provision_type_t;

void dev_config_wifi(void);


#endif