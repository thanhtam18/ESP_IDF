#ifndef _HTTP_SERVER_H
#define _HTTP_SEVER_H
#include <stdint.h>


typedef void (*http_wifi_callback_t) (char* data, int len);

void start_webserver(void);
void stop_webserver(void);
void http_set_wifi_callback(void *cb);


#endif