#include <stdio.h>

#include "../inc/solicita_dados.h"
#include "../inc/envia_dados.h"
#include "../inc/definicoes_gerais.h"
#include "../inc/comunicacao_i2c_bme280.h"
#include "../inc/comunicacao_i2c_lcd.h"


int main(int argc, const char * argv[])
{
    // int uart0_filestream = -1;
    // inicia_bme280();
    testa_lcd();

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