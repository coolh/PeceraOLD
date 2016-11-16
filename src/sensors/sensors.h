#ifndef SENSORS_H
#define SENSORS_H
// Estructura de retorno de DHT22
struct dhsensor {
  float temp;
  float hum;
};

// Leo temperatura
struct dhsensor dht22Read();

#endif
