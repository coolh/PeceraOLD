#include "constants.h"
#include "lcd.h"
#include "menu.h"

// Variables Globales
unsigned char menu_option 		= 0;
int 					button					= 0;
unsigned long last_push 			= 0;
unsigned long last_update			= 0;
bool					power_save 			= FALSE;

// Muestro Bienvenida
void menuWelcome() {
	lcdPrint(0, 0, "CONTROL PECERA");
	lcdPrint(0, 1, "VERSION: " VERSION );
	delay(1000);
	lcdClear();
}


void menuMain() {
	// Manejo del menu
	if (button == BTN_UP && menu_option % 10 == 0) {
		if (menu_option > MENU_ESTADO && menu_option <= MENU_CONFIG) {
			menu_option = menu_option - 10;
		}
	}
	if (button == BTN_DOWN && menu_option % 10 == 0) {
		if (menu_option >= MENU_ESTADO && menu_option < MENU_CONFIG) {
			menu_option = menu_option + 10;
		}
	}
	if (button == BTN_LEFT) {
		if (menu_option > MENU_ESTADO && menu_option <= MENU_ESTADO_EXIT) {
			menu_option--;
		}
		if (menu_option > MENU_CONFIG && menu_option <= MENU_CONFIG_EXIT) {
			menu_option--;
		}
	}
	if (button == BTN_RIGHT) {
		if (menu_option >= MENU_ESTADO && menu_option < MENU_ESTADO_EXIT) {
			menu_option++;
		}
		if (menu_option >= MENU_CONFIG && menu_option < MENU_CONFIG_EXIT) {
			menu_option++;
		}
	}
	if (button == BTN_SELECT && (menu_option == MENU_ESTADO_EXIT || menu_option == MENU_CONFIG_EXIT)) {
		menu_option = MENU_INACTIVO;
		menuInactivo();
		return;
	}

	// Limpio Pantalla
	lcdClear();

	// Ejecuto menues
	switch (menu_option) {
		case MENU_INACTIVO: {
			menuInactivo();
		}
		break;
		case MENU_ESTADO: {
			lcdPrint(0, 0, "     ESTADO     ");
			lcdPrint(0, 1, "    OPCIONES   >");
		}
		break;
		case MENU_ESTADO_LEDS: {
			lcdPrint(0, 0, "BC:100%   R:100%");
			lcdPrint(0, 1, "BF:100%   A: 10%");
		}
		break;
		case MENU_ESTADO_TEMP1: {
			lcdPrint(0, 0, "TEMP AGUA:   27C");
			lcdPrint(0, 1, "--__-_._--.-_._-");
		}
		break;
		case MENU_ESTADO_TEMP2: {
			lcdPrint(0, 0, "TEMP AIRE:   33C");
			lcdPrint(0, 1, "--_.-_-_-.-._-_-");
		}
		break;
		case MENU_ESTADO_HUMIDITY: {
			lcdPrint(0, 0, "HUMEDAD:     94%");
			lcdPrint(0, 1, "-._.-_-_--.-_._-");
		}
		break;
		case MENU_ESTADO_FANS: {
			lcdPrint(0, 0, "FANS:        80%");
			lcdPrint(0, 1, "--_.-_-_..._-_-.");
		}
		break;
		case MENU_ESTADO_DATETIME: {
			lcdPrint(0, 0, "HORA:   22:53:10");
			lcdPrint(0, 1, "FECHA:  29/11/16");
		}
		break;
		case MENU_ESTADO_MICRO: {
			unsigned long uptime = millis();
			volatile double hours = (double)uptime / 3600000;
			char buffer[11];
			String text = dtostrf(hours, 10, 2, buffer);
			lcdPrint(0, 0, "UP: " + text + " H");
			lcdPrint(0, 1, "VERSION:   " VERSION );
		}
		break;
		case MENU_ESTADO_EXIT: {
			lcdPrint(0, 0, "                ");
			lcdPrint(0, 1, "<    SALIDA     ");
		}
		break;
		case MENU_CONFIG: {
			lcdPrint(0, 0, "   CONFIGURAR   ");
			lcdPrint(0, 1, "    OPCIONES   >");
		}
		break;
		case MENU_CONFIG_LIGHTS: {
			lcdPrint(0, 0, "   CONFIGURAR   ");
			lcdPrint(0, 1, "< MANUAL LIGHT >");
		}
		break;
		case MENU_CONFIG_TIMERS: {
			lcdPrint(0, 0, "   CONFIGURAR   ");
			lcdPrint(0, 1, "<  TIMERS DAY  >");
		}
		break;
		case MENU_CONFIG_TIMERS_NITE: {
			lcdPrint(0, 0, "   CONFIGURAR   ");
			lcdPrint(0, 1, "< TIMERS NIGHT >");
		}
		break;
		case MENU_CONFIG_FANS: {
			lcdPrint(0, 0, "   CONFIGURAR   ");
			lcdPrint(0, 1, "<     FANS     >");
		}
		break;
		case MENU_CONFIG_DATE: {
			lcdPrint(0, 0, "   CONFIGURAR   ");
			lcdPrint(0, 1, "< FECHA Y HORA >");
		}
		break;
		case MENU_CONFIG_EXIT: {
			lcdPrint(0, 0, "                ");
			lcdPrint(0, 1, "<    SALIDA     ");
		}
		break;
	}
}

void menuInactivo() {
	// Limpio Pantalla
	lcdClear();

	// Muestro info basica
	lcdPrint(0, 0, "WT:28C     18:25");
	lcdPrint(0, 1, "T:32C    Hr:100%");
}

void menuUpdate() {
	// Variables

	// Leo boton
	button = lcdReadButtons();

	// Delay para evitar repetir teclas
	if (button != BTN_NONE) {
		delay(300);
	}

	// Detecto Inactividad
	if (millis() - last_push >= INAC_TIMEOUT && millis() - last_push <= POWERSAVE_TIMEOUT) {
		menu_option = MENU_INACTIVO;
	}

	// Apago el display
	if (millis() - last_push > POWERSAVE_TIMEOUT) {
		power_save = TRUE;
		lcdOff();
		digitalWrite(BACKLIT, LOW);
	}

	// Entro al menu con select y seteo el default
	if (button == BTN_SELECT && menu_option == MENU_INACTIVO) {
		menu_option = MENU_ESTADO;
	}

	// Entro al menu de configuración (menu_status de 10 a 19)
	if (button != BTN_NONE || millis() - last_update > 1000) {
		menuMain();
		last_update = millis();
	}

	// Seteo estado pulsacion
	if (button != BTN_NONE) {
		last_push = millis();
		// Prendo el display
		if(power_save == TRUE) {
			digitalWrite(BACKLIT, HIGH);
			lcdOn();
			power_save = FALSE;
		}
	}
}
