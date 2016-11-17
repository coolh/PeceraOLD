#ifndef SENSORS_H
#define SENSORS_H

// Estructura de retorno de DHT22
struct dhsensor {
  float temp;
  float hum;
};

// Inicializo DHT22
void dhtInit();

// Leo temperatura
struct dhsensor dht22Read();

// Historico de sensores
void sensorStore();

#endif
