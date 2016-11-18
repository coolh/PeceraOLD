#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <stdio.h>

#include "constants/constants.h"
#include "sensors.h"

// Variables Globales
DHT_Unified dht(DHTPIN, DHTTYPE);
dhsensor dhsensor;
unsigned long last_sensor_read = 0;
unsigned long last_sensor_store = 0;
float air_temp[18]  = { -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000 };
float hum[18]	  		= { -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000 };

// Inicializo DHT22
void dhtInit() {
  dht.begin();
}

// Leo temperatura
struct dhsensor dht22Read() {
  if (millis() - last_sensor_read > 5000) {
    // Print temp and hum
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    dhsensor.temp = event.temperature;
    dht.humidity().getEvent(&event);
    dhsensor.hum = event.relative_humidity;
    last_sensor_read = millis();
  }
  return dhsensor;
}

// Historico de sensores
void sensorStore() {
  // Variables
  int i;
  float aTMax = -1000;
  float aTMin = 1000;
  float hMax = -1000;
  float hMin = 1000;

  // Ejecuto cada STORE_DELAY milis del ultimo store
  if (millis() - last_sensor_store > STORE_DELAY) {
    // Si el DHT22 fue escaneado en los ultimos 5 segundos espero
    while (millis() - last_sensor_read < 5000) {
      delay(1000);
    }
    // Muevo valores viejos una posicion atras
    for (i = 1; i < 16; i++) {
      air_temp[i-1] = air_temp[i];
      hum[i-1] = hum[i];
    }
    // Escribo ultimos valores
    // Leo el DHT22
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    air_temp[15] = event.temperature;
    dht.humidity().getEvent(&event);
    hum[15] = event.relative_humidity;
    last_sensor_read = millis();
    last_sensor_store = millis();
    // Busco MAX y MIN
    for (i = 0; i < 16; i++) {
      if (air_temp[i] != -1000) {
        if (air_temp[i] > aTMax)
          aTMax = air_temp[i];
        if (air_temp[i] < aTMin)
          aTMin = air_temp[i];
        if (hum[i] > hMax)
          hMax = hum[i];
        if (air_temp[i] < hMin)
          hMin = hum[i];
      }
    }
    air_temp[16] = aTMin;
    air_temp[17] = aTMax;
    hum[16] = hMin;
    hum[17] = hMax;
  }
}
