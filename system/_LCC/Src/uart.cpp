/*
 * uart.cpp
 *
 *  Created on: 29 џэт. 2019 у.
 *      Author: Oleg
 */


/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_gpio.h"
#include <dev.h>
#include <uart.h>

#ifdef USE_USART1
uart_c<USE_USART1_ARG> Serial1;
#endif

#ifdef USE_USART2
uart_c<USE_USART2_ARG> Serial2;
#endif

#ifdef USE_USART3
uart_c<USE_USART3_ARG> Serial3;
#endif


