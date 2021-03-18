#ifndef COMUNICACAO_UART_H_
#define COMUNICACAO_UART_H_

void abre_uart(int *uart_filestream);
int envia_buffer_tx(int *uart_filestream, unsigned char *tx_buffer, int len_buffer);
int recebe_buffer_rx(int *uart_filestream, unsigned char *rx_buffer);

#endif