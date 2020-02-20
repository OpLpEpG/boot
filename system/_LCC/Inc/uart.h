/*
 * uart.h
 *
 *  Created on: 29 ���. 2019 �.
 *      Author: Oleg
 */

#ifndef UART_H_
#define UART_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_rcc.h"
#include <dev.h>
#include <tools.h>

typedef enum {
	HALFDUPLEX,
	FULDUPLEX
} uart_mode_e;

typedef enum {
	TXE_LO,
	TXE_HI,
	TXE_NONE,
} uart_txe_e;

typedef enum {
	PORTA = GPIOA_BASE,
	PORTB = GPIOB_BASE,
	PORTC = GPIOC_BASE,
	PORTD = GPIOD_BASE
} uart_txe_num_e;

typedef enum {
	PIN0 = LL_GPIO_PIN_0,
	PIN1 = LL_GPIO_PIN_1,
	PIN2 = LL_GPIO_PIN_2,
	PIN3 = LL_GPIO_PIN_3,
	PIN4 = LL_GPIO_PIN_4,
	PIN5 = LL_GPIO_PIN_5,
	PIN6 = LL_GPIO_PIN_6,
	PIN7 = LL_GPIO_PIN_7,
	PIN8 = LL_GPIO_PIN_8,
	PIN9 = LL_GPIO_PIN_9,
	PIN10 = LL_GPIO_PIN_10,
	PIN11 = LL_GPIO_PIN_11,
	PIN12 = LL_GPIO_PIN_12,
	PIN13 = LL_GPIO_PIN_13,
	PIN14 = LL_GPIO_PIN_14,
	PIN15 = LL_GPIO_PIN_15
} uart_txe_pin_e;

typedef enum {
	UART_1 = USART1_BASE,
	UART_2 = USART2_BASE,
	UART_3 = USART3_BASE
} uart_num_e;

//USE_USART3=256,UART_HALFDUPLEX,UART_TXE_1,TXE_PORTC,13

template <uart_num_e UART_NO, uint16_t BUFF_LEN, uart_mode_e UART_MODE, uart_txe_e TX_MODE, uart_txe_num_e PORT, uint32_t PIN>
class uart_c : public dev_c// rwdev_c
{
#ifdef uart
#undef uart
#endif
#ifdef port
#undef port
#endif

private:

 #define uart ((USART_TypeDef *)UART_NO)
 #define port ((GPIO_TypeDef *)PORT)

 //uint8_t b[BUFF_LEN];
 uint32_t BaudRate;

 INLINE_FORCE void txe_rx(void)
 {
	 ((TX_MODE != TXE_NONE)&&(TX_MODE == TXE_LO))?LL_GPIO_SetOutputPin(port, PIN):LL_GPIO_ResetOutputPin(port, PIN);
 }
 INLINE_FORCE void txe_tx(void)
 {
	 ((TX_MODE != TXE_NONE)&&(TX_MODE == TXE_LO))?LL_GPIO_ResetOutputPin(port, PIN):LL_GPIO_SetOutputPin(port, PIN);
 }
public:
    static const uint16_t buflen = BUFF_LEN;
	uart_c(): dev_c() /*rwdev_c(BUFF_LEN, b)*/, BaudRate(115200) {}
    virtual void begin() override
    {
        LL_USART_InitTypeDef USART_InitStruct;// = {0};
		LL_GPIO_InitTypeDef GPIO_InitStruct;// = {0};

		USART_InitStruct.BaudRate = BaudRate;
		USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
		USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
		USART_InitStruct.Parity = LL_USART_PARITY_NONE;
		USART_InitStruct.TransferDirection = LL_USART_DIRECTION_RX;
		USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;

		GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
		if (UART_MODE == HALFDUPLEX)
		   GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
		else
		   GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;

		switch (UART_NO) {
		case UART_1:
			  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
			  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
			  /**USART1 GPIO Configuration
			  PA9   ------> USART1_TX
			  PA10   ------> USART1_RX
			  */
			  GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
			  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
			  if (UART_MODE == FULDUPLEX)
			  {
				  GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
				  GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
				  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
			  }
		break;
		case UART_2:
			  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
			  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
			  /**USART1 GPIO Configuration
			  PA9   ------> USART1_TX
			  PA10   ------> USART1_RX
			  */
			  GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
			  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
			  if (UART_MODE == FULDUPLEX)
			  {
				  GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
				  GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
				  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
			  }
		break;
		case UART_3:
			  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
			  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
			  /**USART1 GPIO Configuration
			  PA9   ------> USART1_TX
			  PA10   ------> USART1_RX
			  */
			  GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
			  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
			  if (UART_MODE == FULDUPLEX)
			  {
				  GPIO_InitStruct.Pin = LL_GPIO_PIN_11;
				  GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
				  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
			  }
		break;
		}
		LL_USART_Init(uart, &USART_InitStruct);
		if (UART_MODE == HALFDUPLEX)
			   LL_USART_ConfigHalfDuplexMode(uart);
		else
			   LL_USART_ConfigAsyncMode(uart);

		if (TX_MODE != TXE_NONE)
		{
			switch (PORT) {
				case PORTA:
					LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
				break;
				case PORTB:
					LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
				break;
				case PORTC:
					LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
				break;
				case PORTD:
					LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
				break;
			}
			GPIO_InitStruct.Pin = PIN;
			GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
			GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
			GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
			LL_GPIO_Init(port, &GPIO_InitStruct);
			txe_rx();
		}
		LL_USART_Enable(uart);
    }
    virtual void end() override
    {
    	LL_USART_Disable(uart);
    	if (TX_MODE != TXE_NONE) LL_GPIO_SetPinMode(port, PIN, LL_GPIO_MODE_FLOATING);
    }
    void setBaudRate(uint32_t BaudRate)
    {
      	this->BaudRate = BaudRate;
      	if (LL_USART_IsEnabled(uart))
      	{
      		uint32_t periphclk;// = LL_RCC_PERIPH_FREQUENCY_NO;
      		LL_RCC_ClocksTypeDef rcc_clocks;

      		LL_RCC_GetSystemClocksFreq(&rcc_clocks);

      		switch (UART_NO) {
    			case UART_1:
    		      LL_USART_SetBaudRate(uart,rcc_clocks.PCLK2_Frequency,BaudRate);
    		    break;
    			case UART_2:
    		      LL_USART_SetBaudRate(uart,rcc_clocks.PCLK1_Frequency,BaudRate);
    		    break;
    			case UART_3:
    		      LL_USART_SetBaudRate(uart,rcc_clocks.PCLK1_Frequency,BaudRate);
    		    break;
      		}
      	}
    }
	errdev_e write(const void* const buf, uint16_t c)
	{
		if (c == 0) return DEV_ERR;
		if (status == DEV_OK)
		{
			uint8_t* p = (uint8_t*) buf;
			status = DEV_TX;
			txe_tx();

			LL_USART_SetTransferDirection(uart, LL_USART_DIRECTION_TX); //6.  Set the TE bit in USART_CR1 to send an idle frame as first transmission.
			do
			{
				while (!LL_USART_IsActiveFlag_TXE(uart));
				LL_USART_TransmitData8(uart,*p++);

			} while (--c > 0);

			while (!LL_USART_IsActiveFlag_TC(uart)); //8.  2 ����� ���� ���� �����������

			LL_USART_SetTransferDirection(uart, LL_USART_DIRECTION_NONE);
			txe_rx();
			status = DEV_OK;
		}
		return status;
	}
	errdev_e read(uint16_t buflen, void* buf, uint16_t* readcnt)
	{
		uint16_t cnt = 0;

		if (status == DEV_OK)
		{
			uint8_t* p = (uint8_t*) buf;

			status = DEV_RX;
			txe_rx();
			LL_USART_SetTransferDirection(uart, LL_USART_DIRECTION_RX);
			uart->SR;
			uart->DR;// clear SR
			do
			{
				while (!LL_USART_IsActiveFlag_RXNE(uart)) if (LL_USART_IsActiveFlag_IDLE(uart))
				{
					LL_USART_SetTransferDirection(uart, LL_USART_DIRECTION_NONE);
					*readcnt = cnt;
					status = DEV_OK;
					return (cnt == 0) ? DEV_ERR: status;
				}
				*p++ = LL_USART_ReceiveData8(uart);
			} while (++cnt < buflen);
		}
		LL_USART_SetTransferDirection(uart, LL_USART_DIRECTION_NONE);
		*readcnt = cnt;
		status = DEV_OK;
		return (cnt == buflen) ? DEV_ERR: status;
	}

};

#ifdef CONFIG_USE_UART1
extern uart_c<UART_1, CONFIG_UART1_BUFF_LEN, CONFIG_UART1_MODE, CONFIG_UART1_TXE, CONFIG_UART1_TXE_PORT, CONFIG_UART1_TXE_PIN> Serial1;
#endif
#ifdef CONFIG_USE_UART2
extern uart_c<UART_2, CONFIG_UART2_BUFF_LEN, CONFIG_UART2_MODE, CONFIG_UART2_TXE, CONFIG_UART2_TXE_PORT, CONFIG_UART2_TXE_PIN> Serial2;
#endif
#ifdef CONFIG_USE_UART3
extern uart_c<UART_3, CONFIG_UART3_BUFF_LEN, CONFIG_UART3_MODE, CONFIG_UART3_TXE, CONFIG_UART3_TXE_PORT, CONFIG_UART3_TXE_PIN> Serial3;
#endif

#endif /* UART_H_ */
