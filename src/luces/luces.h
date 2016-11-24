#ifndef LUCES_H
#define LUCES_H


// Enciendo / apago luces blanco calido
void on_luz_ww();
void off_luz_ww();

// Enciendo / apago luces blanco frio
void on_luz_cw();
void off_luz_cw();

// Enciendo / apago luces rojas
void on_luz_r();
void off_luz_r();

// Enciendo / apago luces azules
void on_luz_b();
void off_luz_b();

// Obtengo / Seteo override de luces
void set_luz_mode(unsigned char* mode);
void get_luz_mode(unsigned char* mode);

// Devuelvo valores actuales de PWM de los leds
void get_luz_state(unsigned char* state);

// Rutina principal de manejo de luces
void controlLuces();

#endif
