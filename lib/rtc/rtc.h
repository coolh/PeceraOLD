#ifndef RTC_H
#define RTC_H

// Estructura de Fecha
struct date {
  unsigned char second;
  unsigned char minute;
  unsigned char hour;
  unsigned char wday;
  unsigned char day;
  unsigned char month;
  unsigned char year;
};

// Inicializo I2C
void wireInit();

/**
 * Convierte un numero binario a BCD
 */
unsigned char bin2bcd(unsigned char bin);

/**
 * Escribo info de hora
 */
void rtcWrite(date datevar);

/**
 * Leo La informacion de reloj
 */
date rtcRead();

#endif
