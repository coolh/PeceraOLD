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
float air_temp[18];
float hum[18];

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
  float aTMax = -100;
  float aTMin = 100;
  float hMax = 0;
  float hMin = 100;

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
    for (i = 1; i < 16; i++) {
      air_temp[i-1] = air_temp[i];
      hum[i-1] = hum[i];
    }
    // Escribo ultimos valores
    air_temp[15] = myDHT22.getTemperatureC();
    hum[15] = myDHT22.getHumidity();
    last_sensor_store = millis();
    // Busco MAX y MIN
    for (i = 0; i < 16; i++) {
      if (air_temp[i] > aTMax)
        aTMax = air_temp[i];
      if (air_temp[i] < aTMin)
        aTMin = air_temp[i];
      if (hum[i] > hMax)
        hMax = air_temp[i];
      if (air_temp[i] < hMin)
        hMin = air_temp[i];
    }
    air_temp[16] = aTMin;
    air_temp[17] = aTMax;
    hum[16] = hMin;
    hum[17] = hMax;
  }
}
