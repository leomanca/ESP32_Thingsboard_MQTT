#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_system.h" //esp_init funtions esp_err_t 
#include "esp_log.h" //for showing logs
#include "nvs_flash.h" //non volatile storage
#include "lwip/err.h" //light weight ip packets error handling
#include "lwip/sys.h" //system applications for light weight ip apps

const char* ssid = "Wokwi-GUEST";
const char* pass = "";


static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id,void *event_data){
  static int retry_num = 0;
  esp_err_t connection_status;
  switch(event_id){
    case WIFI_EVENT_STA_START:
      printf("WiFi connecting...\n");
      esp_wifi_connect(); //Start connection
      break;
    case WIFI_EVENT_STA_CONNECTED:
      printf("WiFi connected\n");
      break;
    case WIFI_EVENT_STA_DISCONNECTED:
      printf("WiFi lost connection\n");
      if(retry_num<5){
          printf("Reconnection attempt %d\n", retry_num);}
          connection_status = esp_wifi_connect(); //Actual reconnection attempt
          if (connection_status == ESP_OK){
            retry_num = 0;
          }
          else{
            retry_num++;
          }
      break;
    case IP_EVENT_STA_GOT_IP:
      printf("Wifi IP acquired!\n");
      break;
    default:
      printf("This is not handled\n");
  }
}


void wifi_connection()
{
    nvs_flash_init();
    esp_netif_init(); //initialise the TCP/IP stack
    esp_event_loop_create_default();     // event loop                    
    esp_netif_create_default_wifi_sta(); // create WiFi station
    wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT(); 
    esp_wifi_init(&wifi_initiation); //     
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL);
    wifi_config_t wifi_configuration = {0}; // initialise wifi_configuration
    strlcpy((char*)wifi_configuration.sta.ssid, ssid, sizeof(wifi_configuration.sta.ssid));
    strlcpy((char*)wifi_configuration.sta.password, pass, sizeof(wifi_configuration.sta.password)); 
    esp_wifi_set_mode(WIFI_MODE_STA); //Set mode
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_configuration); //set configuration
    esp_wifi_start();
    esp_wifi_connect();
    printf( "wifi_init_softap finished. SSID:%s  password:%s",ssid,pass);

    
}