#ifndef BT_CAN_H_
#define BT_CAN_H_
#ifdef CONFIG_PROTOCOL_CAN

#include <dev.h>
#include <tools.h>
#include "stm32f1xx_hal.h"
#include <stm32f1xx_hal_can.h>



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
        hcan.Instance = CAN1;
        hcan.Init.Prescaler = 16;
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

        if (HAL_CAN_Init(&hcan) != HAL_OK)
        {
            status = DEV_ERR;
        }
        else 
        {
            status = DEV_OK;
        }
    }
    virtual void end() override
    {
        HAL_CAN_DeInit(&hcan);
    }
	errdev_e write(const void* const buf, uint16_t c)
    {
		if (c == 0) return DEV_ERR;
		uint8_t* p = (uint8_t*) buf;
        *p = c;

        return DEV_OK;
    }
    errdev_e read(uint16_t buflen, void* buf, uint16_t* readcnt)
    {
		if (0 == buflen) return DEV_ERR;
        *readcnt = 0;
		uint8_t* p = (uint8_t*) buf;
        //HAL_CAN_MessagePending();
        *p = 11;
        return DEV_OK;
    }
};

extern btcan_c<CONFIG_BTCAN_BUFF_LEN> BootCan;
#endif

#endif
