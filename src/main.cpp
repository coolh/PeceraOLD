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
	setTime(current_date.hour,
					current_date.minute,
					current_date.wday,
					current_date.month,
					current_date.day,
					current_date.year);
	// Tareas programadas de luces
	Alarm.alarmRepeat(0, 58, 0, on_luz_ww);
	Alarm.alarmRepeat(0, 0, 0, off_luz_ww);

	Alarm.alarmRepeat(18, 00, 0, on_luz_cw);
	Alarm.alarmRepeat(23, 00, 0, off_luz_cw);

	Alarm.alarmRepeat(17, 15, 0, on_luz_r);
	Alarm.alarmRepeat(0, 30, 0, off_luz_r);

	Alarm.alarmRepeat(0, 0, 0, on_luz_b);
	Alarm.alarmRepeat(3, 0, 0, off_luz_b);
}

// Main loop
void loop() {
	// Proceso Menu
	menuUpdate();
	sensorsRead();
	sensorsStore();
	controlLuces();
	Alarm.delay(0);
}
