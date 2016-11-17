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
	//lcdInit();
	// Inicializo I2C
	//wireInit();
	// Inicializo Serial
	Serial.begin(9600);
	// Inicializo DHT22
	//dhtInit();
	// Muestro bienvenida
	//menuWelcome();
	// Muestro menu inactivo
	//menuInactivo();

	delay(5000);
}

// Main loop
void loop() {
	pinMode(47, OUTPUT);
	delay(3000);
	digitalWrite(47, HIGH);
	digitalWrite(LED_BUILTIN, HIGH);
	digitalWrite(47, LOW);
	delay(15);
	pinMode(47, INPUT_PULLUP);
	delay(3000);
	digitalWrite(LED_BUILTIN, LOW);
	delay(500);
	//dhsensor dhsensor;
	//dht22Read();
	//delay(2000);
	//Serial.println(millis());
	// Guardo historico de sensores
	//sensorStore();
	// Proceso Menu
	// menuUpdate();
}
