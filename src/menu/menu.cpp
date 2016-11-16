#include "constants/constants.h"

#include "menu.h"
#include "lcd/lcd.h"
#include "rtc/rtc.h"
#include "sensors/sensors.h"

// Variables Globales
unsigned int menu_option 			= 25;
unsigned int button						= 0;
bool				 force_update			= FALSE;

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
			// Variables
			bool salir = FALSE;
			char linea1[17];
			char linea2[17];
			unsigned char option = 0;

			// Imprimo titulo
			lcdPrint(0, 0, "   CONFIGURAR   ");
			lcdPrint(0, 1, "< FECHA Y HORA >");
			if (button == BTN_SELECT) {
				// Leo la hora
				date datevar = rtcRead();
				// Imprimo menu
				sprintf(linea1, "HORA:   %02d:%02d:%02d", datevar.hour, datevar.minute, datevar.second);
				sprintf(linea2, "FECHA:  %02d/%02d/%02d", datevar.day, datevar.month, datevar.year);
				lcdPrint(0, 0, linea1);
				lcdPrint(0, 1, linea2);

				// Entro en el bucle de configuracion
				while (salir == FALSE) {
					// Leo botones
					button = lcdReadButtons();
					// Espero 200ms
					delay(200);
					// Configuro variables de fecha
					switch (option) {
						// Hour
						case 0: {
							lcdPrint(9, 0, "");
							lcdCursor(TRUE);
							switch (button) {
								case BTN_UP: {
									if (datevar.hour < 23) {
										datevar.hour++;
										sprintf(linea1, "%02d", datevar.hour);
										lcdPrint(8, 0, linea1);
									}
									else {
										datevar.hour = 0;
										sprintf(linea1, "%02d", datevar.hour);
										lcdPrint(8, 0, linea1);
									}
								}
								break;
								case BTN_DOWN: {
									if (datevar.hour > 0) {
										datevar.hour--;
										sprintf(linea1, "%02d", datevar.hour);
										lcdPrint(8, 0, linea1);
									}
									else {
										datevar.hour = 23;
										sprintf(linea1, "%02d", datevar.hour);
										lcdPrint(8, 0, linea1);
									}
								}
								break;
								case BTN_RIGHT: {
									if (option < 5) {
										option++;
									}
									else {
										option = 0;
									}
								}
								break;
								case BTN_LEFT: {
									if (option > 0) {
										option--;
									}
									else {
										option = 5;
									}
								}
								break;
							}
						}
						break;
						// Minute
						case 1: {
							lcdPrint(12, 0, "");
							lcdCursor(TRUE);
							switch (button) {
								case BTN_UP: {
									if (datevar.minute < 59) {
										datevar.minute++;
										sprintf(linea1, "%02d", datevar.minute);
										lcdPrint(11, 0, linea1);
									}
									else {
										datevar.minute = 0;
										sprintf(linea1, "%02d", datevar.minute);
										lcdPrint(11, 0, linea1);
									}
								}
								break;
								case BTN_DOWN: {
									if (datevar.minute > 0) {
										datevar.minute--;
										sprintf(linea1, "%02d", datevar.minute);
										lcdPrint(11, 0, linea1);
									}
									else {
										datevar.minute = 59;
										sprintf(linea1, "%02d", datevar.minute);
										lcdPrint(11, 0, linea1);
									}
								}
								break;
								case BTN_RIGHT: {
									if (option < 5) {
										option++;
									}
									else {
										option = 0;
									}
								}
								break;
								case BTN_LEFT: {
									if (option > 0) {
										option--;
									}
									else {
										option = 5;
									}
								}
								break;
							}

						}
						break;
						// Second
						case 2: {
							lcdPrint(15, 0, "");
							lcdCursor(TRUE);
							switch (button) {
								case BTN_UP: {
									if (datevar.second < 59) {
										datevar.second++;
										sprintf(linea1, "%02d", datevar.second);
										lcdPrint(14, 0, linea1);
									}
									else {
										datevar.second = 0;
										sprintf(linea1, "%02d", datevar.second);
										lcdPrint(14, 0, linea1);
									}
								}
								break;
								case BTN_DOWN: {
									if (datevar.second > 0) {
										datevar.second--;
										sprintf(linea1, "%02d", datevar.second);
										lcdPrint(14, 0, linea1);
									}
									else {
										datevar.second = 59;
										sprintf(linea1, "%02d", datevar.second);
										lcdPrint(14, 0, linea1);
									}
								}
								break;
								case BTN_RIGHT: {
									if (option < 5) {
										option++;
									}
									else {
										option = 0;
									}
								}
								break;
								case BTN_LEFT: {
									if (option > 0) {
										option--;
									}
									else {
										option = 5;
									}
								}
								break;
							}
						}
						break;
						// Day
						case 3: {
							lcdPrint(9, 1, "");
							lcdCursor(TRUE);
							switch (button) {
								case BTN_UP: {
									if (datevar.day < 31) {
										datevar.day++;
										sprintf(linea2, "%02d", datevar.day);
										lcdPrint(8, 1, linea2);
									}
									else {
										datevar.day = 0;
										sprintf(linea2, "%02d", datevar.day);
										lcdPrint(8, 1, linea2);
									}
								}
								break;
								case BTN_DOWN: {
									if (datevar.day > 0) {
										datevar.day--;
										sprintf(linea2, "%02d", datevar.day);
										lcdPrint(8, 1, linea2);
									}
									else {
										datevar.day = 31;
										sprintf(linea2, "%02d", datevar.day);
										lcdPrint(8, 1, linea2);
									}
								}
								break;
								case BTN_RIGHT: {
									if (option < 5) {
										option++;
									}
									else {
										option = 0;
									}
								}
								break;
								case BTN_LEFT: {
									if (option > 0) {
										option--;
									}
									else {
										option = 5;
									}
								}
								break;
							}
						}
						break;
						// Month
						case 4: {
							lcdPrint(12, 1, "");
							lcdCursor(TRUE);
							switch (button) {
								case BTN_UP: {
									if (datevar.month < 12) {
										datevar.month++;
										sprintf(linea2, "%02d", datevar.month);
										lcdPrint(11, 1, linea2);
									}
									else {
										datevar.month = 0;
										sprintf(linea2, "%02d", datevar.month);
										lcdPrint(11, 1, linea2);
									}
								}
								break;
								case BTN_DOWN: {
									if (datevar.month > 0) {
										datevar.month--;
										sprintf(linea2, "%02d", datevar.month);
										lcdPrint(11, 1, linea2);
									}
									else {
										datevar.month = 12;
										sprintf(linea2, "%02d", datevar.month);
										lcdPrint(11, 1, linea2);
									}
								}
								break;
								case BTN_RIGHT: {
									if (option < 5) {
										option++;
									}
									else {
										option = 0;
									}
								}
								break;
								case BTN_LEFT: {
									if (option > 0) {
										option--;
									}
									else {
										option = 5;
									}
								}
								break;
							}
						}
						break;
						// Year
						case 5: {
							lcdPrint(15, 1, "");
							lcdCursor(TRUE);
							switch (button) {
								case BTN_UP: {
									if (datevar.year < 99) {
										datevar.year++;
										sprintf(linea2, "%02d", datevar.year);
										lcdPrint(14, 1, linea2);
									}
									else {
										datevar.year = 0;
										sprintf(linea2, "%02d", datevar.year);
										lcdPrint(14, 1, linea2);
									}
								}
								break;
								case BTN_DOWN: {
									if (datevar.year > 0) {
										datevar.year--;
										sprintf(linea2, "%02d", datevar.year);
										lcdPrint(14, 1, linea2);
									}
									else {
										datevar.year = 99;
										sprintf(linea2, "%02d", datevar.year);
										lcdPrint(14, 1, linea2);
									}
								}
								break;
								case BTN_RIGHT: {
									if (option < 5) {
										option++;
									}
									else {
										option = 0;
									}
								}
								break;
								case BTN_LEFT: {
									if (option > 0) {
										option--;
									}
									else {
										option = 5;
									}
								}
								break;
							}

						}
						break;
					}

					// Salgo al apretar SELECT
					if (button == BTN_SELECT) {
						salir = TRUE;
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
	unsigned long last_button_push 	= 0;
	unsigned long last_menu_update	= 0;
	bool					power_save 				= FALSE;

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
	if ((button != BTN_NONE) || (millis() - last_menu_update > 1000) || (force_update == TRUE)) {
		last_menu_update = millis();
		force_update = FALSE;
		menuMain();
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
