#include "constants.h"
#include "lcd.h"
#include "menu.h"
#include "rtc.h"

// Setup
void setup() {
	// Inicializo LCD
	lcdInit();
	// Inicializo I2C
	wireInit();
	// Inicializo Serial
	Serial.begin(9600);
	// Seteo Salidas
	pinMode(BACKLIT, OUTPUT); // Control de backlight del LCD
	// Activo backlight
	digitalWrite(BACKLIT, HIGH);
	// Muestro bienvenida
	menuWelcome();
	// Muestro menu inactivo
	menuInactivo();
}

// Main loop
void loop() {
	// Proceso Menu
	menuUpdate();

	// Leo hora
	date datevar = rtcRead();

	// Pauso
	//delay(500);
}
