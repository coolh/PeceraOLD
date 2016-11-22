#include <TimeLib.h>
#include <TimeAlarms.h>

#include "constants/constants.h"
#include "lcd/lcd.h"
#include "menu/menu.h"
#include "rtc/rtc.h"
#include "sensors/sensors.h"
#include "luces/luces.h"

// variables

// Setup
void setup() {
	// Inicializo LCD
	lcdInit();
	// Inicializo I2C
	wireInit();
	// Inicializo ds18B20
	dsInit();
	// Inicializo DHT22
	dhtInit();
	// Inicializo Serial
	Serial.begin(9600);
	// Muestro bienvenida
	menuWelcome();
	// Muestro menu inactivo
	menuInactivo();

	// Sync date
	date current_date = rtcRead();
	setTime(current_date.hour, current_date.minute,	current_date.wday, current_date.month, current_date.day, current_date.year);

	// Tareas programadas
	Alarm.timerRepeat(WATER_READ_DELAY, readWaterTemp);
	Alarm.timerRepeat(AIR_READ_DELAY, dht22Read);
	Alarm.timerRepeat(STORE_DELAY, sensorStore);
}

// Main loop
void loop() {
	// Proceso Menu
	menuUpdate();
	Alarm.delay(0);
}
