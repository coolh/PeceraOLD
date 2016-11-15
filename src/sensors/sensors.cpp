#include <DHT22.h>
#include <stdio.h>

#include "constants/constants.h"
#include "sensors.h"

// Variables Globales
DHT22 myDHT22(DHTPIN);

dhsensor dhsensor;
unsigned long lastread = 0;

// Leo temperatura
struct dhsensor dht22Read() {
  if (millis() - lastread > 5000) {
    if (myDHT22.readData() == DHT_ERROR_NONE) {
      myDHT22.readData();
      dhsensor.temp = myDHT22.getTemperatureC();
      dhsensor.hum = myDHT22.getHumidity();
      lastread = millis();
    }
  }
  return dhsensor;
}
