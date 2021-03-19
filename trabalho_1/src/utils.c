#include <time.h>

void espera_nsecs(long nsecs)
{
    struct timespec tempo_espera;
    tempo_espera.tv_sec = 0;
    tempo_espera.tv_nsec = nsecs;
    clock_nanosleep(CLOCK_MONOTONIC, 0, &tempo_espera, NULL);
}

int checa_temp_valida(float temperatura)
{
    if(temperatura < 20.0 || temperatura > 100.0)
    {
        return 0;
    }
    else
    {
        return 1;
    }

}
