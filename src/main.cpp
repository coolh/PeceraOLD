#include "constants.h"
#include "lcd.h"
#include "menu.h"
#include "rtc.h"
#include "sensors.h"

// variables
date datevar;

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
	menuUpdate();
}
