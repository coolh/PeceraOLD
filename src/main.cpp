#include "constants/constants.h"
#include "lcd/lcd.h"
#include "menu/menu.h"
#include "rtc/rtc.h"
#include "sensors/sensors.h"

// variables

// Setup
void setup() {
	digitalWrite(LED_BUILTIN, LOW);
	// Inicializo LCD
	lcdInit();
	// Inicializo I2C
	wireInit();
	// Inicializo Serial
	Serial.begin(9600);
	// Inicializo DHT22
	dhtInit();
	// Muestro bienvenida
	menuWelcome();
	// Muestro menu inactivo
	menuInactivo();
}

// Main loop
void loop() {
	// Guardo historico de sensores
	sensorStore();
	// Proceso Menu
	menuUpdate();
}
