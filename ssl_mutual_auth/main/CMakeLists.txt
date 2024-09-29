idf_component_register(SRCS "app_main.c" "dev_app_config.c" "dev_http_server.c" "app_mqtt.c" "app_nvs.c"
                    INCLUDE_DIRS ".")

set(req json_parser json_generator)