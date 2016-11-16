#include "constants/constants.h"
#include "lcd/lcd.h"
#include "menu/menu.h"
#include "rtc/rtc.h"
#include "sensors/sensors.h"

// variables

// Setup
void setup() {
	// Inicializo LCD
	lcdInit();
	// Inicializo I2C
	wireInit();
	// Inicializo Serial
	Serial.begin(9600);

	// Muestro bienvenida
	menuWelcome();

	// Muestro menu inactivo
	menuInactivo();
}

// Main loop
void loop() {
	// Variables

	// Proceso Menu
	//menuUpdate();
	// Guardo historico de sensores
	sensorStore();
}
