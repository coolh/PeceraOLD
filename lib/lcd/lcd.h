#ifndef LCD_H
#define LCD_H
#include <WString.h>

// Inicializa LCD
void lcdInit();

// Imprimo en la posicion
void lcdPrint(int x, int y, String text);

// Read the buttons
int lcdReadButtons();

// Clear LCD
void lcdClear();

// Apago LCD
void lcdOff();

// Prendo LCD
void lcdOn();

// autoscroll
void lcdScroll(bool state);

#endif
