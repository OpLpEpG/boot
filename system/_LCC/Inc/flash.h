/*
 * flash.h
 *
 *  Created on: 4 февр. 2019 г.
 *      Author: Oleg
 */

#ifndef FLASH_H_
#define FLASH_H_

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_flash.h"
#include "stm32f1xx_hal_flash_ex.h"
#include <dev.h>
#include <tools.h>

#define PAGE 1024

typedef enum {
        RESULT_GOOD = 0xFFFFFFFFU,
		RESULT_PART = 0xFFFFFFFEU,
		RESULT_ERR =  0xEEEEEEEEU,
} program_flash_e;



class flash_c : public dev_c// rwdev_c
{
 private:
	INLINE_FORCE bool isPageStart(uint32_t adr) {return (adr % PAGE) == 0;}

	program_flash_e erase(uint32_t adr)
	{
		FLASH_EraseInitTypeDef ei;
		uint32_t pageerror = 0;

	    ei.TypeErase   = FLASH_TYPEERASE_PAGES;
		ei.PageAddress = adr;
		ei.NbPages     = 1;

		HAL_FLASHEx_Erase(&ei, &pageerror);

		return (program_flash_e) pageerror;
	}

 public:
    program_flash_e programm(uint32_t adr, uint32_t cnt, const void* data)
    {
    	program_flash_e res = RESULT_PART;

    	uint32_t* p = (uint32_t*) data;

    	if (HAL_FLASH_Unlock() != HAL_OK) return RESULT_ERR;

    	for (uint32_t cur_adr = adr; cur_adr < adr+cnt; cur_adr += 4)
    	{
    		if (isPageStart(cur_adr))
    		{
    			res = erase(cur_adr);

    			if (res != RESULT_GOOD) break;
    		}
    		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, cur_adr, *p++) != HAL_OK)
    		{
    			res = (program_flash_e) cur_adr;

    			break;
    		}
    	}
    	HAL_FLASH_Lock();

    	return res;
    }
};


#endif /* FLASH_H_ */
