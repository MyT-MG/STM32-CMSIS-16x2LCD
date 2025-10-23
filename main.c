#include "stm32f1xx.h"
#include "lcd.h"

void delay_ms(uint32_t ms){
    for(uint32_t i=0;i<ms*800;i++) __NOP();
}

int main(void){
    LiquidCrystal lcd;

    // Define LCD pins (Port A)
    lcd.port = GPIOA;
    lcd.RS = 0;
    lcd.EN = 1;
    lcd.D4 = 2;
    lcd.D5 = 3;
    lcd.D6 = 4;
    lcd.D7 = 5;

    LiquidCrystal_begin(&lcd, 16, 2);
    LiquidCrystal_setCursor(&lcd, 0, 0);
    LiquidCrystal_print(&lcd, "Hello STM32!");
    LiquidCrystal_setCursor(&lcd, 0, 1);
    LiquidCrystal_print(&lcd, "LiquidCrystal");

    while(1){
        delay_ms(500);
    }
}
