#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../inc/crc16.h"
#include "../inc/definicoes_gerais.h"
#include "../inc/comunicacao_uart.h"

void envia_int(int *uart_filestream)
{
    // abre a uart
    abre_uart(uart_filestream);

    // obtem o inteiro a ser enviado
    bytesInt num;
    printf("digite o inteiro que sera enviado: ");
    scanf(" %d", &num.valor_int);

    // monta o buffer para transferencia
    const int LEN_BUFFER_TX = 5 + sizeof(int);
    unsigned char tx_buffer[LEN_BUFFER_TX];
    unsigned char *p_tx_buffer;

    p_tx_buffer = &tx_buffer[0];
    *p_tx_buffer++ = COD_ARDUINO;
    *p_tx_buffer++ = COD_CMD_ESCREVE;
    *p_tx_buffer++ = CMD_ENVIA_INT;
    *p_tx_buffer++ = num.bytes[0];
    *p_tx_buffer++ = num.bytes[1];
    *p_tx_buffer++ = num.bytes[2];
    *p_tx_buffer++ = num.bytes[3];

    bytesShort crc_tx_calculado;
    crc_tx_calculado.valor_short = calcula_CRC(tx_buffer, (LEN_BUFFER_TX - 2));
    *p_tx_buffer++ = crc_tx_calculado.bytes[0];
    *p_tx_buffer++ = crc_tx_calculado.bytes[1];

    int len_buffer_tx = p_tx_buffer - &tx_buffer[0];

    // envia o buffer via tx
    envia_buffer_tx(uart_filestream, tx_buffer, len_buffer_tx);

    // recebe o buffer via rx
    unsigned char rx_buffer[256];
    int len_buffer_rx = recebe_buffer_rx(uart_filestream, rx_buffer);

    // printa os dados do buffer rx
    printf("tamanho do buffer: %d\n", len_buffer_rx);
    printf("endereco: %X\ncodigo: %X\nsub-codigo: %X\n", rx_buffer[0],
            rx_buffer[1], rx_buffer[2]);
    checa_CRC(rx_buffer, len_buffer_rx);
    int num_rx;
    memcpy(&num_rx, &rx_buffer[3], sizeof(int));
    printf("inteiro retornado: %d\n", num_rx);
}

void envia_float(int *uart_filestream)
{
    // abre a uart
    abre_uart(uart_filestream);

    // obtem o inteiro a ser enviado
    float num = 0;
    printf("digite o float que sera enviado: ");
    scanf(" %f", &num);
    // unsigned char num_char[4];
    // memcpy(num_char, &num, sizeof(int));
    unsigned char *num_char = (unsigned char*) &num;

    // monta o buffer para transferencia
    const int LEN_BUFFER_TX = 5 + sizeof(float);
    unsigned char tx_buffer[LEN_BUFFER_TX];
    unsigned char *p_tx_buffer;

    p_tx_buffer = &tx_buffer[0];
    *p_tx_buffer++ = COD_ARDUINO;
    *p_tx_buffer++ = COD_CMD_ESCREVE;
    *p_tx_buffer++ = CMD_ENVIA_FLOAT;
    *p_tx_buffer++ = num_char[0];
    *p_tx_buffer++ = num_char[1];
    *p_tx_buffer++ = num_char[2];
    *p_tx_buffer++ = num_char[3];

    bytesShort crc_tx_calculado;
    crc_tx_calculado.valor_short = calcula_CRC(tx_buffer, (LEN_BUFFER_TX - 2));
    *p_tx_buffer++ = crc_tx_calculado.bytes[0];
    *p_tx_buffer++ = crc_tx_calculado.bytes[1];

    int len_buffer_tx = p_tx_buffer - &tx_buffer[0];

    // envia o buffer via tx
    envia_buffer_tx(uart_filestream, tx_buffer, len_buffer_tx);

    // recebe o buffer via rx
    unsigned char rx_buffer[256];
    int len_buffer_rx = recebe_buffer_rx(uart_filestream, rx_buffer);

    // printa os dados do buffer rx
    printf("tamanho do buffer: %d\n", len_buffer_rx);
    printf("endereco: %X\ncodigo: %X\nsub-codigo: %X\n", rx_buffer[0],
            rx_buffer[1], rx_buffer[2]);
    checa_CRC(rx_buffer, len_buffer_rx);
    float num_rx;
    memcpy(&num_rx, &rx_buffer[3], sizeof(float));
    printf("float retornado: %f\n", num_rx);
}

void envia_string(int *uart_filestream)
{
    // abre a uart
    abre_uart(uart_filestream);

    // monta o buffer para transferencia
    unsigned char string[] = "Deu bom!";
    const int LEN_STRING = 9;
    const int LEN_BUFFER_TX = 15;
    unsigned char tx_buffer[LEN_BUFFER_TX];
    unsigned char *p_tx_buffer;

    p_tx_buffer = &tx_buffer[0];
    *p_tx_buffer++ = COD_ARDUINO;
    *p_tx_buffer++ = COD_CMD_ESCREVE;
    *p_tx_buffer++ = CMD_ENVIA_STRING;
    *p_tx_buffer++ = LEN_STRING;
    for(int i = 0; i < LEN_STRING; i++)
    {
        *p_tx_buffer++ = string[i];
    }

    bytesShort crc_tx_calculado;
    crc_tx_calculado.valor_short = calcula_CRC(tx_buffer, (LEN_BUFFER_TX - 2));
    *p_tx_buffer++ = crc_tx_calculado.bytes[0];
    *p_tx_buffer++ = crc_tx_calculado.bytes[1];

    int len_buffer_tx = p_tx_buffer - &tx_buffer[0];

    // envia o buffer via tx
    envia_buffer_tx(uart_filestream, tx_buffer, len_buffer_tx);

    // recebe o buffer via rx
    unsigned char rx_buffer[256];
    int len_buffer_rx = recebe_buffer_rx(uart_filestream, rx_buffer);

    // printa os dados do buffer rx
    printf("tamanho do buffer: %d\n", len_buffer_rx);
    printf("endereco: %X\ncodigo: %X\nsub-codigo: %X\n", rx_buffer[0],
            rx_buffer[1], rx_buffer[2]);
    checa_CRC(rx_buffer, len_buffer_rx);
    unsigned char len_string = rx_buffer[3];
    int fim_string = 4 + (unsigned int) len_string;

    printf("string retornada: ");
    for(int i = 4; i < fim_string; i++)
    {
        printf("%c", rx_buffer[i]);
    }
    printf("\n");
}