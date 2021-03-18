#include <time.h>

void espera_nsecs(long nsecs)
{
    struct timespec tempo_espera;
    tempo_espera.tv_sec = 0;
    tempo_espera.tv_nsec = nsecs;
    clock_nanosleep(CLOCK_MONOTONIC, 0, &tempo_espera, NULL);
}