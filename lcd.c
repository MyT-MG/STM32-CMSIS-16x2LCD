#include "lcd.h"
#include <stdint.h>

// Simple delay
static void delay_us(uint32_t us) {
    for(uint32_t i=0; i < us * 8; i++) __NOP();
}

static void lcd_enable(LiquidCrystal *lcd) {
    lcd->port->BSRR = (1 << lcd->EN);
    delay_us(50);
    lcd->port->BRR  = (1 << lcd->EN);
    delay_us(50);
}

static void lcd_send4bits(LiquidCrystal *lcd, uint8_t data) {
    lcd->port->BRR = (0xF << lcd->D4); // Clear data pins
    lcd->port->BSRR = ((data & 0x0F) << lcd->D4);
    lcd_enable(lcd);
}

static void lcd_command(LiquidCrystal *lcd, uint8_t cmd) {
    lcd->port->BRR = (1 << lcd->RS); // RS=0 for command
    lcd_send4bits(lcd, cmd >> 4);
    lcd_send4bits(lcd, cmd & 0x0F);
    delay_us(2000);
}

static void lcd_writeChar(LiquidCrystal *lcd, char c) {
    lcd->port->BSRR = (1 << lcd->RS); // RS=1 for data
    lcd_send4bits(lcd, c >> 4);
    lcd_send4bits(lcd, c & 0x0F);
    delay_us(2000);
}

// ===== public API =====
void LiquidCrystal_begin(LiquidCrystal *lcd, uint8_t cols, uint8_t rows) {
    lcd->cols = cols;
    lcd->rows = rows;

    // Enable GPIO clock
    if(lcd->port == GPIOA) RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    if(lcd->port == GPIOB) RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    if(lcd->port == GPIOC) RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // Configure pins as output 2MHz push-pull
    uint8_t pins[] = {lcd->RS, lcd->EN, lcd->D4, lcd->D5, lcd->D6, lcd->D7};
    for(int i=0; i<6; i++){
        if(pins[i] < 8){
            lcd->port->CRL &= ~(0xF << (pins[i]*4));
            lcd->port->CRL |=  (0x2 << (pins[i]*4));
        } else {
            lcd->port->CRH &= ~(0xF << ((pins[i]-8)*4));
            lcd->port->CRH |=  (0x2 << ((pins[i]-8)*4));
        }
    }

    delay_us(40000); // Wait for LCD power-up

    lcd_command(lcd, 0x33);
    lcd_command(lcd, 0x32);
    lcd_command(lcd, 0x28); // 4-bit, 2 line
    lcd_command(lcd, 0x0C); // Display ON
    lcd_command(lcd, 0x06); // Entry mode
    LiquidCrystal_clear(lcd);
}

void LiquidCrystal_clear(LiquidCrystal *lcd) {
    lcd_command(lcd, 0x01);
    delay_us(2000);
}

void LiquidCrystal_setCursor(LiquidCrystal *lcd, uint8_t col, uint8_t row) {
    uint8_t address = (row == 0) ? 0x00 : 0x40;
    address += col;
    lcd_command(lcd, 0x80 | address);
}

void LiquidCrystal_print(LiquidCrystal *lcd, const char *str) {
    while(*str) lcd_writeChar(lcd, *str++);
}

void LiquidCrystal_write(LiquidCrystal *lcd, char c) {
    lcd_writeChar(lcd, c);
}
