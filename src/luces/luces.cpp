#include "constants/constants.h"
#include "luces.h"

unsigned char luz_ww_on = FALSE;
unsigned char luz_cw_on = FALSE;
unsigned char luz_r_on = FALSE;
unsigned char luz_b_on = FALSE;

unsigned char luz_ww_state;
unsigned char luz_cw_state;
unsigned char luz_r_state;
unsigned char luz_b_state;

unsigned long last_pass;

/*******************************************************************************
 * Enciendo / apago luces blanco calido
 ******************************************************************************/
void on_luz_ww() {
  luz_ww_on = TRUE;
}
void off_luz_ww() {
  luz_ww_on = FALSE;
}

/*******************************************************************************
 * Enciendo / apago luces blanco frio
 ******************************************************************************/
void on_luz_cw() {
  luz_cw_on = TRUE;
}
void off_luz_cw() {
  luz_cw_on = FALSE;
}

/*******************************************************************************
 * Enciendo / apago luces rojas
 ******************************************************************************/
void on_luz_r() {
  luz_r_on = TRUE;
}
void off_luz_r() {
  luz_r_on = FALSE;
}

/*******************************************************************************
 * Enciendo / apago luces azules
*******************************************************************************/
void on_luz_b() {
  luz_b_on = TRUE;
}
void off_luz_b() {
  luz_b_on = FALSE;
}

/*******************************************************************************
 * Devuelvo valores actuales de PWM de los leds
 ******************************************************************************/
void stateLuces(unsigned char state[]) {

  state[0] = (float)luz_ww_state / 255 * 100;
  state[1] = (float)luz_cw_state / 255 * 100;
  state[2] = (float)luz_r_state / 255 * 100;
  state[3] = (float)luz_b_state / 255 * 100;
}

/*******************************************************************************
 * Rutina principal de manejo de luces (0.255 constante para ajustar en segundos
 * el retardo entre incrementos de analogWrite)
 ******************************************************************************/
void controlLuces() {
  if (millis() - last_pass > DIM_INTERVAL / 0.255) {
    // Luz Blanca calida
    if (luz_ww_on && luz_ww_state <= 254) {
      luz_ww_state++;
      analogWrite(WW_LED_PIN, luz_ww_state);
    }
    if (!luz_ww_on && luz_ww_state > 0) {
      luz_ww_state--;
      analogWrite(WW_LED_PIN, luz_ww_state);
    }
    // Luz Blanca fria
    if (luz_cw_on && luz_cw_state <= 254) {
      luz_cw_state++;
      analogWrite(CW_LED_PIN, luz_cw_state);
    }
    if (!luz_cw_on && luz_cw_state > 0) {
      luz_cw_state--;
      analogWrite(CW_LED_PIN, luz_cw_state);
    }
    // Luz roja
    if (luz_r_on && luz_r_state <= 254) {
      luz_r_state++;
      analogWrite(R_LED_PIN, luz_r_state);
    }
    if (!luz_r_on && luz_r_state > 0) {
      luz_r_state--;
      analogWrite(R_LED_PIN, luz_r_state);
    }
    // Luz azul
    if (luz_b_on && luz_b_state <= 254) {
      luz_b_state++;
      analogWrite(B_LED_PIN, luz_b_state);
    }
    if (!luz_b_on && luz_b_state > 0) {
      luz_b_state--;
      analogWrite(B_LED_PIN, luz_b_state);
    }
    last_pass = millis();
  }
}
