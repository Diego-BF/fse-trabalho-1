#include <stdio.h>
#include <time.h>
#include "../inc/bme280.h"
#include "../inc/utils.h"

int obtem_temperatura_externa(float *temp_externa)
{
    int T, P, H; // calibrated values

    int bme_init_status = bme280Init(1, 0x76);
    if (bme_init_status != 0)
    {
        return -1; // problem - quit
    }
    espera_nsecs(TEMPO_50MS); // wait for data to settle for first read

    int i = 0;
    float temp_float = 0.0;
    int temperatura_valida = 0;
    while (!temperatura_valida && i < 2) // read values twice a second for 1 minute
    {
        bme280ReadValues(&T, &P, &H);
        T += 4;
        temp_float = (float)T/100.0;
        temperatura_valida = checa_temp_valida(temp_float);
        if (!temperatura_valida)
        {
            i++;
            espera_nsecs(TEMPO_50MS);
        }
        else
        {
            *temp_externa = temp_float;
        }
    }

    return 0;
}
