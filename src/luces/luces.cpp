#include "constants/constants.h"
#include "luces.h"

int i;
unsigned char luz_mode[4];
unsigned char luz_state[4];
unsigned long last_pass;

/*******************************************************************************
 * Enciendo / apago luces blanco calido
 ******************************************************************************/
void on_luz_ww() {
  if (luz_mode[0] != MAN_ON && luz_mode[0] != MAN_OFF)
    luz_mode[0] = AUTO_ON;
}
void off_luz_ww() {
  if (luz_mode[0] != MAN_ON && luz_mode[0] != MAN_OFF)
    luz_mode[0] = AUTO_OFF;
}

/*******************************************************************************
 * Enciendo / apago luces blanco frio
 ******************************************************************************/
void on_luz_cw() {
  if (luz_mode[2] != MAN_ON && luz_mode[2] != MAN_OFF)
    luz_mode[2] = AUTO_ON;
}
void off_luz_cw() {
  if (luz_mode[2] != MAN_ON && luz_mode[2] != MAN_OFF)
    luz_mode[2] = AUTO_OFF;
}

/*******************************************************************************
 * Enciendo / apago luces rojas
 ******************************************************************************/
void on_luz_r() {
  if (luz_mode[1] != MAN_ON && luz_mode[1] != MAN_OFF)
    luz_mode[1] = AUTO_ON;
}
void off_luz_r() {
  if (luz_mode[1] != MAN_ON && luz_mode[1] != MAN_OFF)
    luz_mode[1] = AUTO_OFF;
}

/*******************************************************************************
 * Enciendo / apago luces azules
*******************************************************************************/
void on_luz_b() {
  if (luz_mode[3] != MAN_ON && luz_mode[3] != MAN_OFF)
    luz_mode[3] = AUTO_ON;
}
void off_luz_b() {
  if (luz_mode[3] != MAN_ON && luz_mode[3] != MAN_OFF)
    luz_mode[3] = AUTO_OFF;
}

/*******************************************************************************
 * Obtengo / Seteo override de luces
 ******************************************************************************/
void set_luz_mode(unsigned char* mode) {
  for (i = 0; i < 4; i++)
    luz_mode[i] = mode[i];
}

void get_luz_mode(unsigned char* mode) {
  for (i = 0; i < 4; i++)
    mode[i] = luz_mode[i];
}

/*******************************************************************************
 * Devuelvo valores actuales de PWM de los leds
 ******************************************************************************/
void get_luz_state(unsigned char* state) {
  for (i = 0; i < 4; i++)
    state[i] = (float)luz_state[i] / 255 * 100;
}

/*******************************************************************************
 * Rutina principal de manejo de luces (0.255 constante para ajustar en segundos
 * el retardo entre incrementos de analogWrite)
 ******************************************************************************/
void controlLuces() {
  if (millis() - last_pass > DIM_INTERVAL / 0.255) {
    for (i = 0; i < 4; i++) {
      if (luz_mode[i] == AUTO_ON && luz_state[i] <= 254)
        luz_state[i]++;
      if (luz_mode[i] == AUTO_OFF && luz_state[i] > 0)
        luz_state[i]--;
      if (luz_mode[i] == MAN_ON)
        luz_state[i] = 255;
      if (luz_mode[i] == MAN_OFF)
        luz_state[i] = 0;
    }
    last_pass = millis();
    // Escribo valores en leds
    analogWrite(WW_LED_PIN, luz_state[0]);
    analogWrite(R_LED_PIN, luz_state[1]);
    analogWrite(CW_LED_PIN, luz_state[2]);
    analogWrite(B_LED_PIN, luz_state[3]);
  }
}
