#ifndef SENSORS_H
#define SENSORS_H

// Inicializo DHT22
void dhtInit();

// Inicializo ds18B20
void dsInit();

// Leo temperatura
void dht22Read();

// Historico de sensores
void sensorStore();

// Leo sensor de temperatura del agua
void readWaterTemp();

#endif
