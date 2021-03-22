#ifndef COMUNICACAO_I2C_LCD_H_
#define COMUNICACAO_I2C_LCD_H_

#define I2C_ADDR_LCD   0x27 // I2C device address

void exibe_dado_lcd(float temp_interna, float temp_externa, float temp_ref);

void lcd_init(int *fd_ref);

#endif
