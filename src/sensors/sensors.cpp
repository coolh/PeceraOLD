#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <stdio.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "constants/constants.h"
#include "sensors.h"

// Inicializo onewire
OneWire ds(ONEWIREPIN);
DallasTemperature sensors(&ds);

// Inicializo DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);

// Variables Globales
float air_temp[19]    = { -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, 0 };
float humidity[19]	  = { -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, 0 };
float water_temp[19]	= { -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, 0 };

/*******************************************************************************
 * Inicializo DHT22
 ******************************************************************************/
void dhtInit() {
  dht.begin();
}

/*******************************************************************************
 * Inicializo ds18B20
 ******************************************************************************/
void dsInit() {
  sensors.begin();
}

/*******************************************************************************
 * Leo sensores
 ******************************************************************************/
void sensorsRead() {
  // Print temp and hum
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  air_temp[18] = event.temperature;
  dht.humidity().getEvent(&event);
  humidity[18] = event.relative_humidity;
  sensors.requestTemperatures();
  water_temp[18] = sensors.getTempCByIndex(0);
}

/*******************************************************************************
 * Historico de sensores
 ******************************************************************************/
void sensorsStore() {
  // Variables
  volatile int i;
  float aTMax = -1000;
  float aTMin = 1000;
  float hMax = -1000;
  float hMin = 1000;
  float wMax = -1000;
  float wMin = 1000;

  // Escribo ultimos valores
  air_temp[15] = air_temp[18];
  humidity[15] = humidity[18];
  water_temp[15] = water_temp[18];

  // Muevo valores viejos una posicion atras
  for (i = 1; i < 16; i++) {
    air_temp[i-1] = air_temp[i];
    humidity[i-1] = humidity[i];
    water_temp[i-1] = water_temp[i];
  }

  // Busco MAX y MIN
  for (i = 0; i < 16; i++) {
    if (air_temp[i] != -1000) {
      if (air_temp[i] > aTMax)
        aTMax = air_temp[i];
      if (air_temp[i] < aTMin)
        aTMin = air_temp[i];
      if (humidity[i] > hMax)
        hMax = humidity[i];
      if (humidity[i] < hMin)
        hMin = humidity[i];
      if (water_temp[i] > wMax)
        wMax = water_temp[i];
      if (water_temp[i] < wMin)
        wMin = water_temp[i];
    }
  }
  // Escribo Maximo y minimo
  air_temp[16] = aTMin;
  air_temp[17] = aTMax;
  humidity[16] = hMin;
  humidity[17] = hMax;
  water_temp[16] = wMin;
  water_temp[17] = wMax;
}
