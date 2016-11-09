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
 * Esta funcion establece la cominicación con el DS1307 y lee los registros
 * de fecha y hora. Entrega la informacion horaria en las variables globales
 * declaradas al principio del sketch.
 */
bool rtcWrite(date datevar);

#endif
