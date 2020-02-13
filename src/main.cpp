#include <main.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <dev.h>
#include <uart.h>
#include <crc16.h>
#include <flash.h>


#define PAGE_PART_STD 128

#ifdef PROTOCOL_MODBUS
// bootloader test commad
#define CMD_BOOT      100
// bootloader exit
#define CMD_READ      101
#define CMD_BOOT_EXIT 102
#define CMD_WRITE     103
#define GET_CMD (b[1])
#define CURR_ADR (*(uint32_t*) &b[2])
#define CMD_PREAMB (1+1+4)
#else
// bootloader test commad
#define CMD_BOOT      0x8
// bootloader exit
#define CMD_READ      0xD
#define CMD_BOOT_EXIT 0xE
#define CMD_WRITE     0xF
#define GET_CMD (b[0] & 0x0F)
#define CURR_ADR (*(uint32_t*) &b[1])
#define CMD_PREAMB (1+4)
#endif

#define BUFF_DATA_PTR(b)  &b[CMD_PREAMB]
#define CRC_LEN 2

#define SET_RESULT(b,r) {*(uint32_t*) BUFF_DATA_PTR(b) = (uint32_t) r;}


#ifdef USE_USART1
#define com Serial1
#endif
#ifdef USE_USART2
#define com Serial2
#endif
#ifdef USE_USART3
#define com Serial3
#endif

void SystemClock_Config(void);

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

flash_c flash;

void Setup(void)
{
	  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
	  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	  /* Configure the system clock */
	  SystemClock_Config();
}

void Loop(void)
{
	uint8_t b[com.buflen];
	uint16_t cnt = 0;

	if ((com.read(256, b, &cnt) == DEV_OK) && (crc16(b, cnt) == 0))
	{
		   switch(GET_CMD)
		   {
			   case CMD_BOOT:

				   com.write(b, cnt);

			   break;

			   case CMD_BOOT_EXIT:

				   NVIC_SystemReset();

			   break;

			   case CMD_READ:

				   memcpy(&b[CMD_PREAMB], (const void*)CURR_ADR, PAGE_PART_STD);

				   cnt = CMD_PREAMB + PAGE_PART_STD;

				   SET_CRC16(b, cnt)

				   cnt += CRC_LEN;

				   com.write(b, cnt);

			   break;

			   case CMD_WRITE:

			    if (cnt == CMD_PREAMB + PAGE_PART_STD + CRC_LEN)
				{
			     SET_RESULT(b, flash.programm(CURR_ADR, PAGE_PART_STD, BUFF_DATA_PTR(b)));

				   cnt = CMD_PREAMB + 4;

				   SET_CRC16(b, cnt)

				   cnt += 2;

				   com.write(b, cnt);
				}
			   break;
		   }
	}
}

void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);

   if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2)
  {
    Error_Handler();
  }
  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_Init1msTick(72000000);
  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
  LL_SetSystemCoreClock(72000000);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
