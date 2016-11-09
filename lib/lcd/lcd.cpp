#include <LiquidCrystal.h>

#include "constants.h"
#include "lcd.h"


// Global Variables
// Inicializo variable para LCD
LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);

void lcdInit() {
   // set up the LCD's number of columns and rows:
   lcd.begin(LCD_COLS, LCD_ROWS);
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

void lcdOff() {
  lcd.noDisplay();
}

void lcdOn() {
  lcd.display();
}

void lcdScroll(bool state) {
  if (state == TRUE) {
    lcd.autoscroll();
  }
  else {
    lcd.noAutoscroll();
  }
}
