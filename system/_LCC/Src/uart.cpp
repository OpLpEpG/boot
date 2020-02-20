/*
 * uart.cpp
 *
 *  Created on: 29 ���. 2019 �.
 *      Author: Oleg
 */


/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_gpio.h"
#include <dev.h>
#include <uart.h>

#ifdef CONFIG_USE_UART1
uart_c<UART_1, CONFIG_UART1_BUFF_LEN, CONFIG_UART1_MODE, CONFIG_UART1_TXE, CONFIG_UART1_TXE_PORT, CONFIG_UART1_TXE_PIN> Serial1;
#endif
#ifdef CONFIG_USE_UART2
uart_c<UART_2, CONFIG_UART2_BUFF_LEN, CONFIG_UART2_MODE, CONFIG_UART2_TXE, CONFIG_UART2_TXE_PORT, CONFIG_UART2_TXE_PIN> Serial2;
#endif
#ifdef CONFIG_USE_UART3
uart_c<UART_3, CONFIG_UART3_BUFF_LEN, CONFIG_UART3_MODE, CONFIG_UART3_TXE, CONFIG_UART3_TXE_PORT, CONFIG_UART3_TXE_PIN> Serial3;
#endif


