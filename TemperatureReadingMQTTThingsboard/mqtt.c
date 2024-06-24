#include "mqtt_client.h"
#include "esp_event.h"


const char* mqtt_broker_uri = "mqtt://demo.thingsboard.io:1883"; // You can use any public MQTT broker
const char* mqtt_topic = "v1/devices/me/telemetry";
const char* ACCESS_TOKEN = "";
const char *message = "";

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    esp_mqtt_event_handle_t event = event_data;
    int msg_id;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            printf("MQTT_EVENT_CONNECTED\n");
            break;
        case MQTT_EVENT_DISCONNECTED:
            printf("MQTT_EVENT_DISCONNECTED\n");
            break;
        case MQTT_EVENT_PUBLISHED:
            printf("MQTT_EVENT_PUBLISHED\n");
            break;
        default:
            printf("Other event");
            break;
    }
}

esp_mqtt_client_handle_t mqtt_app_start(void) {
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = mqtt_broker_uri,
        .credentials.username = ACCESS_TOKEN, // Use the access token as the username
        //.credentials.password = "", // No password needed for ThingsBoard
    };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    esp_mqtt_client_start(client);
    return client;
}