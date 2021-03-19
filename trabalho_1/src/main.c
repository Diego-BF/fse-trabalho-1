#include <stdio.h>

#include "../inc/definicoes_gerais.h"
#include "../inc/solicita_dados_uart.h"
#include "../inc/comunicacao_i2c_lcd.h"
#include "../inc/comunicacao_i2c_bme280.h"


int main(int argc, const char * argv[])
{
    float temperatura_interna = 0.0;
    float temperatura_externa = 0.0;
    float temperatura_ref =     0.0;
    float temperatura_potenc =  0.0;

    /* a qualquer momento permitir que o usuario escolha entre colocar uma
    temperatura de referencia ou usar a do potenciometro */
    // obtem temperatura interna
    // obtem temperatura potenciometro
    // obtem temperatura externa
    // obtem temperatura de referencia
    // escrever no arquivo csv os dados medidos
    // calcula pid
    // PID > 0 -> usa a PWN para acionar/controlar o resistor
    // PID <= -40 -> usa a PWN para acionar/controlar a ventoinha

    // const int NUM_ESCOLHAS = 2;
    // int escolha = -1;
    // printf("O que voce deseja fazer?\n");
    // printf("\t1 - solicitar a temperatura interna;\n");
    // printf("\t2 - solicitar a temperatura do potenciometro;\n");

    // while (escolha < 0 || escolha > NUM_ESCOLHAS)
    // {
    //     printf("opção desejada: ");
    //     scanf(" %d", &escolha);
    //     if(escolha < 0 || escolha > NUM_ESCOLHAS)
    //     {
    //         printf("VALOR INVALIDO digite novamente!\n\n\n");
    //     }
    // }

    // switch (escolha)
    // {
    // case 1:
    //     solicita_float(&uart0_filestream, CMD_SOLICITA_TEMP_INT);
    //     break;
    // case 2:
    //     solicita_float(&uart0_filestream, CMD_SOLICITA_TEMP_POT);
    //     break;
    // case 0:
    //     return 0;
    // }

    return 0;
}
