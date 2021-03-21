#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include "../inc/definicoes_gerais.h"
#include "../inc/solicita_dados_uart.h"
#include "../inc/comunicacao_i2c_lcd.h"
#include "../inc/comunicacao_i2c_bme280.h"
#include "../inc/utils.h"

int parar_leitura_temperatura;
int parar_execucao;
int fd_i2c_lcd = -1;
float temperatura_interna = 0.0;
float temperatura_externa = 0.0;
float temperatura_ref =     0.0;
float temperatura_potenc =  0.0;

void *thread_alarme_1s(void *a) {
    sleep(1);
    parar_leitura_temperatura = 1;
    return NULL;
}

void inicia_protocolos(void)
{
    // inicios relacionado ao I2C
    if (wiringPiSetupSys() == -1)
    {
        printf("problema ao fazer o setup do I2C.");
        exit(1);
    }
    fd_i2c_lcd = wiringPiI2CSetup(I2C_ADDR_LCD);
    lcd_init(&fd_i2c_lcd);
}


int main(int argc, const char * argv[])
{
    pthread_t alarme_1s;

    FILE *temps_csv = fopen("temperaturas.csv", "w");
    fprintf(temps_csv, "sep=,\nTI, TE, TP, TR\n");

    inicia_protocolos();

    /* a qualquer momento permitir que o usuario escolha entre colocar uma
    temperatura de referencia ou usar a do potenciometro */

    parar_execucao = 0;
    // while(!parar_execucao)
    // pthread_create(&gerencia_lcd, NULL, thread_gerencia_lcd, NULL);
    for (int i = 0; i < 3; i++)
    {
        // usa thread para servir como alarme quando o tempo de leitura terminar
        parar_leitura_temperatura = 0;
        pthread_create(&alarme_1s, NULL, thread_alarme_1s, NULL);
        // obtem temperatura interna
        solicita_temperatura_uart(CMD_SOLICITA_TEMP_INT, &temperatura_interna);
        // obtem temperatura potenciometro
        solicita_temperatura_uart(CMD_SOLICITA_TEMP_POT, &temperatura_potenc);
        // obtem temperatura externa
        obtem_temperatura_externa(&temperatura_externa);
        // obtem temperatura de referencia
        temperatura_ref = temperatura_potenc + i;
        printf("TI: %2.2f, TE: %2.2f, TP: %2.2f, TR: %2.2f\n",
            temperatura_interna, temperatura_externa, temperatura_potenc,
            temperatura_ref);
        while (!parar_leitura_temperatura)
        {
            espera_nsecs(TEMPO_10MS);
        }
        pthread_join(alarme_1s, NULL);
        exibe_dado_lcd(temperatura_interna,
        temperatura_externa, temperatura_ref);

        // escrever no arquivo csv os dados medidos
        fprintf(temps_csv, "%2.2f,%2.2f,%2.2f,%2.2f\n",
            temperatura_interna, temperatura_externa, temperatura_potenc,
            temperatura_ref);
    }
    parar_execucao = 1;
    // pthread_join(gerencia_lcd, NULL);

    // calcula pid
    // PID > 0 -> usa a PWN para acionar/controlar o resistor
    // PID <= -40 -> usa a PWN para acionar/controlar a ventoinha
    // para e desliga a ventoinha, o resistor e a tela lcd se o usuario quiser
    // para e desliga a ventoinha, o resistor e a tela lcd se receber SIGTERM


    return 0;
}
