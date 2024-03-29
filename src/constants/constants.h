#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <arduino.h>
#include <TimeLib.h>
#include <TimeAlarms.h>

/* Historico de sensores */
extern float air_temp[19];
extern float humidity[19];
extern float water_temp[19];

/* Version */
#define VERSION   "0.0.1"

/* bool */
#define FALSE 0
#define TRUE 1

/* LCD Type */
#define LCD_COLS	16
#define LCD_ROWS	2

/* Botones LCD */
#define	BTN_RIGHT	  0
#define BTN_UP		  1
#define BTN_DOWN 	  2
#define BTN_LEFT   	3
#define BTN_SELECT 	4
#define BTN_NONE   	5

/* Control LCD */
#define RS			8
#define	ENABLE	9
#define D4			4
#define D5			5
#define D6			6
#define D7			7
#define BACKLIT 10

/* Input de botones LCD */
#define KEYPAD_INPUT   0

/* Comm sensor de temperatura */
#define DHTPIN  47
#define DHTTYPE DHT22

/* Temperatura del AGUA */
#define ONEWIREPIN 46

/* Tiempo de inactividad 120s (milisec) */
#define INAC_TIMEOUT  120000UL

/* Tiempo de apagado del display 10m (milisec) */
#define POWERSAVE_TIMEOUT 600000UL

/* Intervalo de guardodo de datos historicos (milisegundos) */
#define STORE_DELAY 1800000UL
/* Intervalo de lectura de sensores (milisegundos) */
#define SENSORS_READ_DELAY 5000UL

/* Estado del menu LCD */
#define MENU_INACTIVO         0
/* Menu estado */
#define MENU_ESTADO           10
#define MENU_ESTADO_LEDS      11
#define MENU_ESTADO_TEMP1     12
#define MENU_ESTADO_TEMP2     13
#define MENU_ESTADO_HUMIDITY  14
#define MENU_ESTADO_FANS      15
#define MENU_ESTADO_DATETIME  16
#define MENU_ESTADO_MICRO     17
#define MENU_ESTADO_EXIT      18
/* Menu Config */
#define MENU_CONFIG             20
#define MENU_CONFIG_LIGHTS      21
#define MENU_CONFIG_TIMERS      22
#define MENU_CONFIG_TIMERS_NITE 23
#define MENU_CONFIG_FANS        24
#define MENU_CONFIG_DATE        25
#define MENU_CONFIG_EXIT        26

/* Useful Constants */
#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24UL)

/* Useful Macros for getting elapsed time */
#define numberOfSeconds(_time_) (_time_ % SECS_PER_MIN)
#define numberOfMinutes(_time_) ((_time_ / SECS_PER_MIN) % SECS_PER_MIN)
#define numberOfHours(_time_) (( _time_% SECS_PER_DAY) / SECS_PER_HOUR)
#define elapsedDays(_time_) ( _time_ / SECS_PER_DAY)

/* RTC Sync delay */
#define RTC_SYNC_DELAY 3600000UL

/* Intervalo de dimming (segundos) */
#define DIM_INTERVAL 60

/* Salidas de control LEDs */
#define WW_LED_PIN  45
#define CW_LED_PIN  44
#define R_LED_PIN   43
#define B_LED_PIN   42

/* light state */
#define AUTO_OFF  0
#define AUTO_ON   1
#define MAN_OFF   2
#define MAN_ON    3

#endif
