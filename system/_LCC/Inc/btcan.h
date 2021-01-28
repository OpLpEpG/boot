#ifndef BT_CAN_H_
#define BT_CAN_H_
#ifdef CONFIG_PROTOCOL_CAN

#include <dev.h>
#include <tools.h>
#include "stm32f1xx_hal.h"
#include <stm32f1xx_hal_can.h>

#define BOOT_ID  0x7E7



template <uint16_t BUFF_LEN>
class btcan_c : public dev_c// rwdev_c
{
private:
    CAN_HandleTypeDef hcan;


public:
    static const uint16_t buflen = BUFF_LEN;

	btcan_c(): dev_c() /*rwdev_c(BUFF_LEN, b), BaudRate(115200)*/ {}

    virtual void begin() override
    {
        status = DEV_OK;

        hcan.Instance = CAN1;
        hcan.Init.Prescaler = 16; // 132352 bt/s
        hcan.Init.Mode = CAN_MODE_NORMAL;
        hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
        hcan.Init.TimeSeg1 = CAN_BS1_12TQ;
        hcan.Init.TimeSeg2 = CAN_BS2_4TQ;
        hcan.Init.TimeTriggeredMode = DISABLE;
        hcan.Init.AutoBusOff = DISABLE;
        hcan.Init.AutoWakeUp = DISABLE;
        hcan.Init.AutoRetransmission = DISABLE;
        hcan.Init.ReceiveFifoLocked = DISABLE;
        hcan.Init.TransmitFifoPriority = DISABLE;

        if (HAL_CAN_Init(&hcan) != HAL_OK) status = DEV_ERR;
        else 
        {
            CAN_FilterTypeDef f;

            f.FilterFIFOAssignment = CAN_FILTER_FIFO0;
            f.FilterBank = 0;
            f.FilterScale = CAN_FILTERSCALE_16BIT;
            f.FilterMode = CAN_FILTERMODE_IDLIST;
            f.FilterActivation = CAN_FILTER_ENABLE;
            f.FilterMaskIdLow = 0;
            f.FilterMaskIdHigh = 0;
            f.FilterIdHigh = 0;
            f.FilterIdLow = BOOT_ID << 5; 

            if (HAL_CAN_ConfigFilter(&hcan, &f) != HAL_OK) status = DEV_ERR;
            else
            {
                if (HAL_CAN_Start(&hcan) != HAL_OK) status = DEV_ERR;                    
            }
        }        
    }
    
    virtual void end() override
    {
        HAL_CAN_Stop(&hcan);
        HAL_CAN_DeInit(&hcan);
    }
	
    errdev_e write(const void* const buf, uint16_t c)
    {
		if (c == 0) return DEV_ERR;

        CAN_TxHeaderTypeDef m;
        m.StdId = BOOT_ID;
        m.IDE = CAN_ID_STD;
        m.RTR = CAN_RTR_DATA;
        m.TransmitGlobalTime = DISABLE;

        uint32_t pTxMailbox;
        uint32_t tickstart = HAL_GetTick();


		uint8_t* p = (uint8_t*) buf;

        while (c > 0)               
        {
           if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) > 0)
           {
               if (c > 8) {m.DLC = 8; c -= 8;}
               else {m.DLC = c; c = 0;}

               if (HAL_CAN_AddTxMessage(&hcan, &m, p, &pTxMailbox) != HAL_OK) return DEV_ERR;
               else tickstart = HAL_GetTick();
               
               p += 8;
           }
           if ((HAL_GetTick() - tickstart) > 10) return DEV_TIMEOUT;
        }
        return DEV_OK;
    }
    
    errdev_e read(uint16_t buflen, void* buf, uint16_t* readcnt)
    {
		if (0 == buflen) return DEV_ERR;

        while (HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_RX_FIFO0) == 0);

        uint32_t tickstart = HAL_GetTick();
		uint8_t* p = (uint8_t*) buf;
        uint16_t n = 0;

        while ((*readcnt <= buflen) && ((HAL_GetTick() - tickstart) < 10))
        {
            CAN_RxHeaderTypeDef h;
           if (HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_RX_FIFO0) > 0) 
                if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &h, p) != HAL_OK) return DEV_ERR;
           p += h.DLC;
           n += h.DLC;
           tickstart = HAL_GetTick();
           if (h.DLC != 8) break;
        }
        *readcnt = n;
        return DEV_OK;
    }
};

extern btcan_c<CONFIG_BTCAN_BUFF_LEN> BootCan;
#endif

#endif
