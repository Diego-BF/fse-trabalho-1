// void type_int(int num);
// void type_float(float num);
// void lcd_loc(int linha); //move cursor
// void clr_lcd(void); // clr LCD return home
// void type_ln(const char *s);
// void type_char(char val);

/*
*
* by Lewis Loflin www.bristolwatch.com lewis@bvu.net
* http://www.bristolwatch.com/rpi/i2clcd.htm
* Using wiringPi by Gordon Henderson
*
*
* Port over lcd_i2c.py to C and added improvements.
* Supports 16x2 and 20x4 screens.
* This was to learn now the I2C lcd displays operate.
* There is no warrenty of any kind use at your own risk.
*
*/

#include <wiringPiI2C.h>
// #include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../inc/utils.h"

// Define some device parameters
#define I2C_ADDR_LCD   0x27 // I2C device address

// Define some device constants
#define LCD_CHR  1 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command

#define LINE1  0x80 // 1st line
#define LINE2  0xC0 // 2nd line

#define LCD_BACKLIGHT   0x08  // On
// LCD_BACKLIGHT = 0x00  # Off

#define ENABLE  0b00000100 // Enable bit

#define TIME_2000MSEC 2000000000L
#define TIME_500MICSEC 5L


int testa_lcd(void);
void lcd_init(void);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);

// added by Lewis
void type_int(int num);
void type_float(float num);
void lcd_loc(int line); //move cursor
void clr_lcd(void); // clr LCD return home
void type_ln(const char *s);
void type_char(char val);

void espera_nsecs(long nanosecs);

// // added by Lewis
// void typeInt(int i);
// void typeFloat(float myFloat);
// void lcd_loc(int line); //move cursor
// void clr_lcd(void); // clr LCD return home
// void type_ln(const char *s);
// void typeChar(char val);
int fd;  // seen by all subroutines

int testa_lcd(void)
{
    // if (wiringPiSetupSys() == -1)
    // {
    //     exit (1);
    // }

    fd = wiringPiI2CSetup(I2C_ADDR_LCD);

    if (fd == -1)
    {
        exit (1);
    }

  //printf("fd = %d ", fd);

  lcd_init(); // setup LCD

    char array1[] = "Hello world!";

    // while (1)
    // {
        lcd_loc(LINE1);
        type_ln("Using wiringPi");
        lcd_loc(LINE2);
        type_ln("Geany editor.");

        espera_nsecs(TIME_2000MSEC);
        clr_lcd();
        lcd_loc(LINE1);
        type_ln("I2c  Programmed");
        lcd_loc(LINE2);
        type_ln("in C not Python.");

        espera_nsecs(TIME_2000MSEC);
        clr_lcd();
        lcd_loc(LINE1);
        type_ln("Arduino like");
        lcd_loc(LINE2);
        type_ln("fast and easy.");

        espera_nsecs(TIME_2000MSEC);
        clr_lcd();
        lcd_loc(LINE1);
        type_ln(array1);

        espera_nsecs(TIME_2000MSEC);
        clr_lcd(); // defaults LINE1
        type_ln("Int  ");
        int value = 20125;
        type_int(value);

        espera_nsecs(TIME_2000MSEC);
        lcd_loc(LINE2);
        type_ln("Float ");
        float FloatVal = 10045.25989;
        type_float(FloatVal);
        espera_nsecs(TIME_2000MSEC);
    // }

    return 0;
}


// float to string
void type_float(float num)
{
    char buffer[20];
    sprintf(buffer, "%4.2f", num);
    type_ln(buffer);
}

// int to string
void type_int(int num)
{
    char array1[20];
    sprintf(array1, "%d", num);
    type_ln(array1);
}

// clr lcd go home loc 0x80
void clr_lcd(void)
{
    lcd_byte(0x01, LCD_CMD);
    lcd_byte(0x02, LCD_CMD);
}

// go to location on LCD
void lcd_loc(int line)
{
    lcd_byte(line, LCD_CMD);
}

// out char to LCD at current position
void type_char(char val)
{
    lcd_byte(val, LCD_CHR);
}


// this allows use of any size string
void type_ln(const char *s)
{
  while ( *s ) lcd_byte(*(s++), LCD_CHR);

}

void lcd_byte(int bits, int mode)
{
    //Send byte to data pins
    // bits = the data
    // mode = 1 for data, 0 for command
    int bits_high;
    int bits_low;
    // uses the two half byte writes to LCD
    bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT ;
    bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT ;

    // High bits
    wiringPiI2CReadReg8(fd, bits_high);
    lcd_toggle_enable(bits_high);

    // Low bits
    wiringPiI2CReadReg8(fd, bits_low);
    lcd_toggle_enable(bits_low);
    }

    void lcd_toggle_enable(int bits)   {
    // Toggle enable pin on LCD display
    espera_nsecs(TIME_500MICSEC);
    wiringPiI2CReadReg8(fd, (bits | ENABLE));
    espera_nsecs(TIME_500MICSEC);
    wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
    espera_nsecs(TIME_500MICSEC);
}

void lcd_init(void)
{
    // Initialise display
    lcd_byte(0x33, LCD_CMD); // Initialise
    lcd_byte(0x32, LCD_CMD); // Initialise
    lcd_byte(0x06, LCD_CMD); // Cursor move direction
    lcd_byte(0x0C, LCD_CMD); // 0x0F On, Blink Off
    lcd_byte(0x28, LCD_CMD); // Data length, number of lines, font size
    lcd_byte(0x01, LCD_CMD); // Clear display
    espera_nsecs(TIME_500MICSEC);
}
