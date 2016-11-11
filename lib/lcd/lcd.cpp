#include <LiquidCrystal.h>
#include "constants.h"
#include "lcd.h"

// Global Variables
// Inicializo variable para LCD
LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);

void lcdInit() {
  // Defino chars para historial
  byte chars[8][8] = {
    { B00000, B00000, B00000, B00000, B00000, B00000, B00000, B11111 },
    { B00000, B00000, B00000, B00000, B00000, B00000, B11111, B11111 },
    { B00000, B00000, B00000, B00000, B00000, B11111, B11111, B11111 },
    { B00000, B00000, B00000, B00000, B11111, B11111, B11111, B11111 },
    { B00000, B00000, B00000, B11111, B11111, B11111, B11111, B11111 },
    { B00000, B00000, B11111, B11111, B11111, B11111, B11111, B11111 },
    { B00000, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
    { B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 }
  };

  // Creo chars para historial
  for ( int i = 0; i < 8; i++) {
    lcd.createChar(i, chars[i]);
  }

  // set up the LCD's number of columns and rows:
  lcd.begin(LCD_COLS, LCD_ROWS);

  // Seteo Salida backlite
  pinMode(BACKLIT, OUTPUT); // Control de backlight del LCD

  // Activo backlight
  digitalWrite(BACKLIT, HIGH);
}

void lcdPrint(int x, int y, String text) {
  // Set Cursor Position
  lcd.setCursor(x, y);
  // Print Text
  lcd.print(text);
}

// read the buttons
int lcdReadButtons(){
  int adc_key_in = analogRead(KEYPAD_INPUT);
  if (adc_key_in > 1000) return BTN_NONE;
  if (adc_key_in < 50)   return BTN_RIGHT;
  if (adc_key_in < 120)  return BTN_UP;
  if (adc_key_in < 280)  return BTN_DOWN;
  if (adc_key_in < 430)  return BTN_LEFT;
  if (adc_key_in < 660)  return BTN_SELECT;

  return BTN_NONE;
}

// Clear LCD
void lcdClear() {
	lcd.clear();
}

void lcdOn(bool state) {
  if (state == TRUE) {
    lcd.display();
  }
  else {
    lcd.noDisplay();
  }
}

// Escribo caracteres especiales
void lcdWriteChar(int x, int y, byte custom_char[8], int mempos) {
  lcd.createChar(mempos, custom_char);
  lcd.setCursor(x, y);
  lcd.write(byte(mempos));
}

void lcdScroll(bool state) {
  if (state == TRUE) {
    lcd.autoscroll();
  }
  else {
    lcd.noAutoscroll();
  }
}
