#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "driver/gpio.h" //Imports GPIOs functionalities
#include <math.h> //Imports math functions
#include "functions.c"
#include "wifi.c"
#include "mqtt.c"

void app_main() {
  char message[50];
  float temp = 0.0;
  int led_value = 0;
  wifi_connection();
  wait(5000); // make sure wifi is on
  esp_mqtt_client_handle_t client = mqtt_app_start();
  if (client == NULL) {
        printf("Failed to start MQTT. Program ended");
        return;
    }
  printf("TEMPERATURE READING IN PROGRESS...\n");
  gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
  gpio_set_direction(ADC_GPIO, GPIO_MODE_INPUT);
  
  while (true) {
    led_value = (led_value == 0) ? 1 : 0;
    gpio_set_level(LED_PIN, led_value);
    temp = readTemperature();
    if (temp == 0.0) {
      wait(1000);
    }
    else{
      printf("TEMP : %.2f\n", temp);
      snprintf(message, sizeof(message), "{\"temperature\":%.2f}", temp);
      int msg_id = esp_mqtt_client_publish(client, mqtt_topic, message, 0, 1, 0);
      if (msg_id != -1) {
        printf("Published message successfully\n");
        printf("Message: %s\n", message);
        }
        else {
          printf("Failed to publish message\n");
        }
      temp = 0.0;
      wait(2000);
    }
  }
}



