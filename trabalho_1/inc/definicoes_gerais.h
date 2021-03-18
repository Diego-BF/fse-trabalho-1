#ifndef DEFINICOES_GERAIS_H_
#define DEFINICOES_GERAIS_H_

#include <stdint.h>

#define COD_ARDUINO 0x01
#define COD_CMD_SOLICITA 0x23
#define COD_CMD_ESCREVE 0x16

// #define CMD_SOLICITA_INT    0xA1
// #define CMD_SOLICITA_FLOAT  0xA2
// #define CMD_SOLICITA_STRING 0xA3
#define CMD_SOLICITA_TEMP_INT  0xC1
#define CMD_SOLICITA_TEMP_POT  0xC2

#define CMD_ENVIA_INT    0xB1
#define CMD_ENVIA_FLOAT  0xB2
#define CMD_ENVIA_STRING 0xB3

#define PORTA_I2C        1
#define END_I2C_BME      0x76
#define END_I2C_LCD      0x27

typedef union {
    short valor_short;
    uint8_t bytes[2];
} bytesShort;

typedef union {
    int valor_int;
    uint8_t bytes[4];
} bytesInt;

#endif