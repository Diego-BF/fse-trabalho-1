#include <stdio.h>
#include <unistd.h>         //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>        //Used for UART
#include <time.h>
#include "../inc/definicoes_gerais.h"

void abre_uart(int *uart_filestream)
{
    // tenta abrir a UART0 na raspberry
    *uart_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);      //Open in non blocking read/write mode
    // testa se a abertura foi bem sucedida
    if (*uart_filestream == -1)
    {
        printf("Erro - Não foi possível iniciar a UART.\n");
    }
    // else
    // {
    //     printf("UART inicializada!\n");
    // }
    // cria a struct para armazenar as options da termios e obtem as que estao em uso na UART0 atualmente
    struct termios options;
    tcgetattr(*uart_filestream, &options);
    // sobrescreve as options com as flags desejadas
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;     //<Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    // limpa os dados atualmente na filestream UART0 e seta com os atributos configurados acima
    tcflush(*uart_filestream, TCIFLUSH);
    tcsetattr(*uart_filestream, TCSANOW, &options);
}

int envia_buffer_tx(int *uart_filestream, unsigned char *tx_buffer, int len_buffer)
{
    // printf("DEBUG RAW buffer (0x): ");
    for (int i = 0; i < len_buffer; i++)
    {
        printf(" %X", tx_buffer[i]);
    }
    printf("\n");

    // printf("Buffers de memória criados!\n");

    if (*uart_filestream != -1)
    {
        // printf("Escrevendo caracteres na UART ...");
        int count = write(*uart_filestream, &tx_buffer[0], len_buffer);
        if (count < 0)
        {
            printf("UART TX error\n");
            return -1;
        }
        // else
        // {
        //     printf("escrito.\n");
        // }
    }
    // sleep(1);
    struct timespec tempo100ms;
    tempo100ms.tv_sec = 0;
    tempo100ms.tv_nsec = 100000000L;
    nanosleep(&tempo100ms, NULL);

    return 0;
}

int recebe_buffer_rx(int *uart_filestream, unsigned char *rx_buffer)
{
    int rx_length = -1;

    //----- CHECK FOR ANY RX BYTES -----
    if (*uart_filestream != -1)
    {
        // Read up to 255 characters from the port if they are there
        rx_length = read(*uart_filestream, (void*) rx_buffer, 255);      //Filestream, buffer to store in, number of bytes to read (max)
        if (rx_length < 0)
        {
            printf("Erro na leitura.\n"); //An error occured (will occur if there are no bytes)
        }
        else if (rx_length == 0)
        {
            printf("Nenhum dado disponível.\n"); //No data waiting
        }
    }

    close(*uart_filestream);

    return rx_length;
}