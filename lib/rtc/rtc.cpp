#include <Wire.h>
#include "rtc.h"

/**
* Esta funcion inicializa las comunicaciones I2C con el shield de RTC
*/
void wireInit() {
  // Inicializo I2C
  Wire.begin();
}

/**
 * Esta funcion establece la cominicación con el DS1307 y lee los registros
 * de fecha y hora. Entrega la informacion horaria en las variables globales
 * declaradas al principio del sketch.
 */
void rtcWrite(date datevar) {
  // Iniciar el intercambio de información con el DS1307 (0x68)
  Wire.beginTransmission(0x68);
  // Escribir la dirección del registro segundero
  Wire.write(0x00);
  // Escribir valores en los registros, nos aseguramos que el bit clock halt
  // Del registro del segundero este desactivado
  Wire.write(bin2bcd(datevar.second & 0x7F));
  Wire.write(bin2bcd(datevar.minute));
  Wire.write(bin2bcd(datevar.hour));
  Wire.write(bin2bcd(datevar.wday));
  Wire.write(bin2bcd(datevar.day));
  Wire.write(bin2bcd(datevar.month));
  Wire.write(bin2bcd(datevar.year));
}

/**
 * Esta funcion establece la cominicación con el DS1307 y lee los registros
 * de fecha y hora.
 */

date rtcRead()
{
  date datevar;
  // Iniciar el intercambio de información con el DS1307 (0xD0)
  Wire.beginTransmission(0x68);

  // Escribir la dirección del segundero
  Wire.write(0x00);

  // Si el DS1307 esta presente, comenzar la lectura de 8 bytes
  Wire.requestFrom(0x68, 8);

  // Recibimos el byte del registro 0x00 y lo convertimos a binario
  datevar.second = bcd2bin(Wire.read());
  datevar.minute = bcd2bin(Wire.read()); // Continuamos recibiendo cada uno de los registros
  datevar.hour = bcd2bin(Wire.read());
  datevar.wday = bcd2bin(Wire.read());
  datevar.day = bcd2bin(Wire.read());
  datevar.month = bcd2bin(Wire.read());
  datevar.year = bcd2bin(Wire.read());

  return datevar;
}

/**
 * Convierte un numero binario a BCD
 */
unsigned char bin2bcd(unsigned char bin) {
  return (bin / 10 * 16) + (bin % 10);
}
