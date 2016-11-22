#ifndef RTC_H
#define RTC_H

// Estructura de Fecha
struct date {
  unsigned int second;
  unsigned int minute;
  unsigned int hour;
  unsigned int wday;
  unsigned int day;
  unsigned int month;
  unsigned int year;
};

// Inicializo I2C
void wireInit();

/**
 * Convierte un numero binario a BCD
 */
unsigned int bin2bcd(unsigned int bin);


/**
 * Convierte un numero BCD a binario
 */
unsigned int bcd2bin(unsigned int bcd);

/**
 * Escribo info de hora
 */
void rtcWrite(date datevar);

/**
 * Leo La informacion de reloj
 */
struct date rtcRead();

/**
 * Sincronizo RTC con hora del micro
 */
void rtcSync();

#endif
