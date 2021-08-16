/*
 * Copyright (c) 2015-2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== gpiointerrupt.c ========
 */
#include <stdint.h>
#include <stddef.h>

//printf重定向有关头文件
#include <stdio.h>
#include <string.h>
#include <ti/devices/msp432e4/inc/msp432e401y.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/apps/LED.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/Timer.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/******************************定义结构体*********************************/
//定义LED结构体
LED_Handle ledHandle;
LED_Params ledParams;
//定义Timer结构体
Timer_Handle timerHandle;
Timer_Params timerParams;
/*************************************************************************/

/********************其他函数(如参数初始化、回调函数)***********************/
//定时器回调函数
void TimerCallBackFxn(Timer_Handle handle, int_fast16_t status)
{
    LED_toggle(ledHandle);
    printf("LED Toggle\r\n");
}

//计时器参数控制函数
void My_Timer_Params(Timer_Params *params)
{
    params->timerMode = Timer_CONTINUOUS_CALLBACK;
    params->periodUnits = Timer_PERIOD_HZ;
    params->timerCallback = TimerCallBackFxn;
    params->period = 10;
}
/*************************************************************************/

/*
 *  ======== mainThread ========
 */
void* mainThread(void *arg0)
{
    /********************************LED************************************/
    LED_init();
    LED_Params_init(&ledParams);
    ledHandle = LED_open(CONFIG_LED_0, &ledParams);
    if (ledHandle == NULL)
    {
        // LED_open() failed
        printf("LED_open() failed!!!\r\n");
        while (1)
            ;
    }
    /***********************************************************************/

    /*******************************Timer***********************************/
    Timer_init();
    My_Timer_Params(&timerParams);
    timerHandle = Timer_open(CONFIG_TIMER_0, &timerParams);
    if (timerHandle == NULL)
    {
        // Timer_open() failed
        printf("Timer_open() failed!!!\r\n");
        while (1)
            ;
    }
    //开启计时器
    if (Timer_start(timerHandle) == Timer_STATUS_ERROR)
    {
        /* Failed to start timer */
        printf("Timer_start() failed!!!\r\n");
        while (1)
            ;
    }
    /***********************************************************************/

    return (NULL);
}
