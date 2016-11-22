#ifndef SENSORS_H
#define SENSORS_H

// Inicializo DHT22
void dhtInit();

// Inicializo ds18B20
void dsInit();

// Leo temperatura
void sensorsRead();

// Historico de sensores
void sensorsStore();

#endif
