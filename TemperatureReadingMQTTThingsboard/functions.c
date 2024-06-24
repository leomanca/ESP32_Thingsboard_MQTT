// MACROS
#define ADC_GPIO ADC1_CHANNEL_7 // GPIO35
#define LED_PIN 33

float readTemperature(){
  const float BETA = 3950; // should match the Beta Coefficient of the thermistor
  int analogValue = adc1_get_raw(ADC_GPIO);
  float celsius = 1 / (log(1 / (4095. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15; //the ADCs in ESP32 are 12 bits
  return celsius;
}

void wait(int time){
  // Give time in ms please
  vTaskDelay(time / portTICK_PERIOD_MS);
}