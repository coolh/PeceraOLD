#ifndef LCD_H
#define LCD_H

// Inicializa LCD
void lcdInit();

// Imprimo en la posicion
void lcdPrint(int x, int y, String text);

// Read the buttons
int lcdReadButtons();

// Clear LCD
void lcdClear();

// Prendo y apago LCD
void lcdOn(bool state);

// Escribo un caracter customizable
void lcdWriteChar(int x, int y, byte custom_char[8], int mempos);

#endif
