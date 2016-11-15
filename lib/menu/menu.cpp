#include "constants.h"

#include "menu.h"
#include "lcd.h"
#include "rtc.h"
#include "sensors.h"

// Variables Globales
unsigned int menu_option 			= 0;
unsigned int button						= 0;
unsigned long last_button_push 	= 0;
unsigned long last_menu_update	= 0;
bool					power_save 				= FALSE;
bool					force_update			= FALSE;

// Muestro Bienvenida
void menuWelcome() {
	lcdPrint(0, 0, "CONTROL PECERA");
	lcdPrint(0, 1, "VERSION: " VERSION );
	delay(1000);
	//lcdClear();
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
	//lcdClear();

	// Ejecuto menues
	switch (menu_option) {
		case MENU_INACTIVO: {
			menuInactivo();
		}
		break;
		case MENU_ESTADO: {
			lcdPrint(0, 0, "     ESTADO     ");
			lcdPrint(0, 1, "  INFORMACION  >");
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
			// Muestro info basica
			date datevar = rtcRead();
			char linea1[17];
			char linea2[17];
			sprintf(linea1, "HORA:   %02d:%02d:%02d", datevar.hour, datevar.minute, datevar.second);
			sprintf(linea2, "FECHA:  %02d/%02d/%02d", datevar.day, datevar.month, datevar.year);
			lcdPrint(0, 0, linea1);
			lcdPrint(0, 1, linea2);
		}
		break;
		case MENU_ESTADO_MICRO: {
			char linea1[17];
			unsigned long uptime = millis() / 1000;
			int days = elapsedDays(uptime);
			int hours = numberOfHours(uptime);
			int mins = numberOfMinutes(uptime);
			sprintf(linea1, "UP: %3dd %2dh %2dm", days, hours, mins);
			lcdPrint(0, 0, linea1);
			lcdPrint(0, 1, "VERSION:   " VERSION);
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
			volatile bool salir = FALSE;
			lcdPrint(0, 0, "   CONFIGURAR   ");
			lcdPrint(0, 1, "< FECHA Y HORA >");
			if (button == BTN_SELECT) {
				// Leo la hora
				date datevar = rtcRead();
				while (salir == FALSE) {
					// Variables
					char linea1[17];
					char linea2[17];
					// Leo botones
					button = lcdReadButtons();
					// Delay para evitar repetir teclas
					if (button != BTN_NONE) {
						Serial.println("button none");
						delay(300);
					}
					sprintf(linea1, "HORA:   %02d:%02d:%02d", datevar.hour, datevar.minute, datevar.second);
					sprintf(linea2, "FECHA:  %02d/%02d/%02d", datevar.day, datevar.month, datevar.year);
					lcdPrint(0, 0, linea1);
					lcdPrint(0, 1, linea2);
					if (button == BTN_SELECT) {
						salir = TRUE;
						Serial.println("Salir");
						force_update = TRUE;
					}
				}
			}
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
	// Variables
	char linea1[17];
	char linea2[17];
	char temp[5];
	char hum[4];

	// Leo la hora
	date datevar = rtcRead();

	// Leo la temperatura y humedad del aire
	dhsensor TyH = dht22Read();
	//convierto float a char
	dtostrf(TyH.temp, 4, 1, temp);
	dtostrf(TyH.hum, 3, 0, hum);
	// Formateo las lineas del LCD
	sprintf(linea1, "W:28.2C    %02d:%02d", datevar.hour, datevar.minute);
	sprintf(linea2, "T:%3sC  Hr:%s%%", temp, hum);

	lcdPrint(0, 0, linea1);
	lcdPrint(0, 1, linea2);
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
	if (millis() - last_button_push >= INAC_TIMEOUT && millis() - last_button_push <= POWERSAVE_TIMEOUT) {
		menu_option = MENU_INACTIVO;
	}

	// Apago el display
	if (millis() - last_button_push > POWERSAVE_TIMEOUT) {
		power_save = TRUE;
		lcdOn(FALSE);
		digitalWrite(BACKLIT, LOW);
	}

	// Entro al menu con select y seteo el default
	if (button == BTN_SELECT && menu_option == MENU_INACTIVO) {
		menu_option = MENU_ESTADO;
	}

	// Muestro menu de configuración al presionar un boton, cada un segundo, y cuando force_update = TRUE
	if (button != BTN_NONE || millis() - last_menu_update > 1000 || force_update == TRUE) {
		menuMain();
		last_menu_update = millis();
		force_update = FALSE;
	}

	// Seteo estado pulsacion
	if (button != BTN_NONE) {
		last_button_push = millis();
		// Prendo el display
		if(power_save == TRUE) {
			digitalWrite(BACKLIT, HIGH);
			lcdOn(TRUE);
			power_save = FALSE;
		}
	}
}
