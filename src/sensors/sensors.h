#ifndef SENSORS_H
#define SENSORS_H

// Estructura de retorno de DHT22
struct dhsensor {
  float temp;
  float hum;
  float wtemp;
};

// Inicializo DHT22
void dhtInit();

// Inicializo ds18B20
void dsInit();

// Leo temperatura
struct dhsensor dht22Read();

// Historico de sensores
void sensorStore();

// Leo sensor de temperatura del agua
float readWaterTemp();

#endif
