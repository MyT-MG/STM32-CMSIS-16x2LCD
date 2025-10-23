#ifndef __LCD_H
#define __LCD_H

#include "stm32f1xx.h"

typedef struct {
    GPIO_TypeDef *port;
    uint8_t RS;
    uint8_t EN;
    uint8_t D4;
    uint8_t D5;
    uint8_t D6;
    uint8_t D7;
    uint8_t cols;
    uint8_t rows;
} LiquidCrystal;

// Function prototypes
void LiquidCrystal_begin(LiquidCrystal *lcd, uint8_t cols, uint8_t rows);
void LiquidCrystal_clear(LiquidCrystal *lcd);
void LiquidCrystal_setCursor(LiquidCrystal *lcd, uint8_t col, uint8_t row);
void LiquidCrystal_print(LiquidCrystal *lcd, const char *str);
void LiquidCrystal_write(LiquidCrystal *lcd, char c);

#endif
