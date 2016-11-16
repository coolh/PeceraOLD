#include <DHT22.h>
#include <stdio.h>

#include "constants/constants.h"
#include "sensors.h"

// Variables Globales
DHT22 myDHT22(DHTPIN);
dhsensor dhsensor;
unsigned long last_sensor_read = 0;
unsigned long last_sensor_store = 0;

// Historico de sensores
unsigned char store_index = 0;
float air_temp[16];
float hum[16];

// Leo temperatura
struct dhsensor dht22Read() {
  if (millis() - last_sensor_read > 5000) {
    if (myDHT22.readData() == DHT_ERROR_NONE) {
      myDHT22.readData();
      dhsensor.temp = myDHT22.getTemperatureC();
      dhsensor.hum = myDHT22.getHumidity();
      last_sensor_read = millis();
    }
  }
  return dhsensor;
}

// Historico de sensores
void sensorStore() {
  // Variables
  int i;

  // Ejecuto cada STORE_DELAY milis del ultimo store
  if (millis() - last_sensor_store > STORE_DELAY) {
    // Si el DHT22 fue escaneado en los ultimos 5 segundos espero
    while (millis() - last_sensor_read < 5000) {
      delay(1000);
    }
    // Leo el DHT22
    if (myDHT22.readData() == DHT_ERROR_NONE) {
      myDHT22.readData();
      last_sensor_read = millis();
    }
    // Muevo valores viejos una posicion atras
    for (i = 15; i > 0; i--) {
      air_temp[i-1] = air_temp[i];
      hum[i-1] = hum[i];
    }
    // Escribo ultimos valores
    air_temp[15] = myDHT22.getTemperatureC();
    hum[15] = myDHT22.getHumidity();
  }
}
