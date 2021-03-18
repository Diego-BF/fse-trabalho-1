#include <stdio.h>
#include <string.h>

#include "../inc/crc16.h"
#include "../inc/definicoes_gerais.h"
#include "../inc/comunicacao_uart.h"

// void solicita_int(int *uart_filestream)
// {
//     // abre a uart
//     abre_uart(uart_filestream);

//     // monta o buffer para transferencia
//     unsigned char tx_buffer[5];
//     unsigned char *p_tx_buffer;

//     p_tx_buffer = &tx_buffer[0];
//     *p_tx_buffer++ = COD_ARDUINO;
//     *p_tx_buffer++ = COD_CMD_SOLICITA;
//     *p_tx_buffer++ = CMD_SOLICITA_INT;

//     bytesShort crc_tx_calculado;
//     crc_tx_calculado.valor_short = calcula_CRC(tx_buffer, 3);
//     *p_tx_buffer++ = crc_tx_calculado.bytes[0];
//     *p_tx_buffer++ = crc_tx_calculado.bytes[1];

//     int len_buffer_tx = p_tx_buffer - &tx_buffer[0];

//     // envia o buffer via tx
//     envia_buffer_tx(uart_filestream, tx_buffer, len_buffer_tx);

//     // recebe o buffer via rx
//     unsigned char rx_buffer[256];
//     int len_buffer_rx = recebe_buffer_rx(uart_filestream, rx_buffer);

//     // checa o crc para ver se a msg esta correta
//     printf("tamanho do buffer: %d\n", len_buffer_rx);
//     printf("endereco: %X\ncodigo: %X\nsub-codigo: %X\n", rx_buffer[0],
//             rx_buffer[1], rx_buffer[2]);
//     checa_CRC(rx_buffer, len_buffer_rx);
//     int num_rx;
//     memcpy(&num_rx, &rx_buffer[3], sizeof(int));
//     printf("inteiro retornado: %d\n", num_rx);
// }

float solicita_float(int *uart_filestream, short sub_cod)
{
    // abre a uart
    abre_uart(uart_filestream);

    // monta o buffer para transferencia
    unsigned char tx_buffer[9];
    unsigned char *p_tx_buffer;

    p_tx_buffer = &tx_buffer[0];
    *p_tx_buffer++ = COD_ARDUINO;
    *p_tx_buffer++ = COD_CMD_SOLICITA;
    *p_tx_buffer++ = sub_cod;
    *p_tx_buffer++ = 0;
    *p_tx_buffer++ = 7;
    *p_tx_buffer++ = 8;
    *p_tx_buffer++ = 9;

    bytesShort crc_tx_calculado;
    crc_tx_calculado.valor_short = calcula_CRC(tx_buffer, 7);
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

    return num_rx;
}

// void solicita_string(int *uart_filestream)
// {
//     // abre a uart
//     abre_uart(uart_filestream);

//     // monta o buffer para transferencia
//     unsigned char tx_buffer[5];
//     unsigned char *p_tx_buffer;

//     p_tx_buffer = &tx_buffer[0];
//     *p_tx_buffer++ = COD_ARDUINO;
//     *p_tx_buffer++ = COD_CMD_SOLICITA;
//     *p_tx_buffer++ = CMD_SOLICITA_STRING;

//     bytesShort crc_tx_calculado;
//     crc_tx_calculado.valor_short = calcula_CRC(tx_buffer, 3);
//     *p_tx_buffer++ = crc_tx_calculado.bytes[0];
//     *p_tx_buffer++ = crc_tx_calculado.bytes[1];

//     int len_buffer_tx = p_tx_buffer - &tx_buffer[0];

//     // envia o buffer via tx
//     envia_buffer_tx(uart_filestream, tx_buffer, len_buffer_tx);

//     // recebe o buffer via rx
//     unsigned char rx_buffer[256];
//     int len_buffer_rx = recebe_buffer_rx(uart_filestream, rx_buffer);

//     // printa os dados do buffer rx
//     printf("tamanho do buffer: %d\n", len_buffer_rx);
//     printf("endereco: %X\ncodigo: %X\nsub-codigo: %X\n", rx_buffer[0],
//             rx_buffer[1], rx_buffer[2]);
//     checa_CRC(rx_buffer, len_buffer_rx);
//     unsigned char len_string = rx_buffer[3];
//     int fim_string = 4 + (unsigned int) len_string;

//     printf("string retornada: ");
//     for(int i = 4; i < fim_string; i++)
//     {
//         printf("%c", rx_buffer[i]);
//     }
//     printf("\n");
// }