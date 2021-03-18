#ifndef COMUNICACAO_I2C_LCD_H_
#define COMUNICACAO_I2C_LCD_H_

int testa_lcd(void);
void lcd_init(void);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);

// added by Lewis
void type_int(int num);
void type_float(float num);
void lcd_loc(int linha); //move cursor
void clr_lcd(void); // clr LCD return home
void type_ln(const char *s);
void type_char(char val);

#endif
