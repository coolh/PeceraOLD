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
 * Esta funcion establece la cominicación con el DS1307 y escribe los registros
 * de fecha y hora.
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
  // Terminamos la escritura y verificamos si el DS1307 respondio
  // Si la escritura se llevo a cabo el metodo endTransmission retorna 0
  Wire.endTransmission();    
}

/**
 * Esta funcion establece la cominicación con el DS1307 y lee los registros
 * de fecha y hora.
 */

struct date rtcRead()
{
  date datevar;

  // Iniciar el intercambio de información con el DS1307 (0xD0)
  Wire.beginTransmission(0x68);

  // Escribir la dirección del segundero
  Wire.write(0x00);

  // Terminamos la escritura y verificamos si el DS1307 respondio
  // Si la escritura se llevo a cabo el metodo endTransmission retorna 0
  if (Wire.endTransmission()) {
    return datevar;
  }

  // Si el DS1307 esta presente, comenzar la lectura de 8 bytes
  Wire.requestFrom(0x68, 7);

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
unsigned int bin2bcd(unsigned int bin) {
  return (bin / 10 * 16) + (bin % 10);
}

/**
 * Convierte un numero BCD a binario
 */
unsigned int bcd2bin(unsigned int bcd) {
  // Convertir decenas y luego unidades a un numero binario
  return (bcd / 16 * 10) + (bcd % 16);
}
