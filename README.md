# ESP32_Thingsboard_MQTT
A small code written in C using Wokwi to simulate an ESP32 that reads data from a temperature sensor and sends it to Thingsboard using the MQTT protocol.  
The code relies on event handlers to connect to the WiFi module.   
When the WiFi connection is successful, the MQTT client is created and a connection with the MQTT broker is then created using the device ID access token provided by Thingsboard for the "ESP32" device created on the cloud.  
After the WiFi module is started, the ESP32 proceeds on reading the data from the temperature sensor.  
The data is then published into the standard topic v1/devices/me/telemetry.  

