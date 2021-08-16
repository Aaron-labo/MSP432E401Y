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
#include <string.h>

//printf重定向有关头文件
#include <ti/devices/msp432e4/inc/msp432e401y.h>
#include <stdio.h>

/* Driver Header files */
#include <ti/drivers/UART.h>


/* Driver configuration */
#include "ti_drivers_config.h"

void ReadCallBackFxn(UART_Handle handle, void *buf, size_t count)
{
    UART_write(handle, buf, count);
    memset(buf, 0, count);
    UART_read(handle, buf, count);
}

void My_UART_Params_init(UART_Params *params)
{
    params->readMode = UART_MODE_BLOCKING;
    params->writeMode = UART_MODE_BLOCKING;
    params->readTimeout = UART_WAIT_FOREVER;
    params->writeTimeout = UART_WAIT_FOREVER;
    params->readCallback = ReadCallBackFxn;
    params->writeCallback = NULL;
    params->readReturnMode = UART_RETURN_FULL;
    params->readDataMode = UART_DATA_TEXT;
    params->writeDataMode = UART_DATA_TEXT;
    params->readEcho = UART_ECHO_OFF;
    params->baudRate = 115200;
    params->dataLength = UART_LEN_8;
    params->stopBits = UART_STOP_ONE;
    params->parityType = UART_PAR_NONE;
    params->custom = NULL;
}

void delay(uint32_t time)
{
    uint32_t i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 10000; j++)
            ;
}

UART_Handle uartHandle;
UART_Params uartParams;

/*
 *  ======== mainThread ========
 */
void* mainThread(void *arg0)
{
    char input[32];
    uint8_t i = 0;
    // Initialize the UART driver.  UART_init() must be called before
    // calling any other UART APIs.
    UART_init();
    // Create a UART with data processing off.
    My_UART_Params_init(&uartParams);

    // Open an instance of the UART drivers
    uartHandle = UART_open(CONFIG_UART_0, &uartParams);
    // UART_open() failed
    while (uartHandle == NULL)
        ;


//    UART_read(uartHandle, input, 1);
    // Loop forever echoing
    while (1)
    {
        printf("初始化成功1234567890!!!%d\r", i++);
        delay(1000);
    }
}

/***********************************printf重定向***************************************/
//须在头文件中添加：
//printf重定向有关头文件
//#include <stdio.h>
//#include <string.h>
//#include <ti/devices/msp432e4/inc/msp432e401y.h>

//须在mainThread函数外需添加：
//定义UART结构体
//UART_Handle uartHandle;
//UART_Params uartParams;

//须在mainThread函数内需添加：
//UART初始化
//UART_init();
//UART_Params_init(&uartParams);
//uartHandle = UART_open(CONFIG_UART_0, &uartParams);

/*
 * 添加下面两个函数可以实现printf重定向
 * 若只有fputc则不能输出格式化字符串，如%d %f
 * 若只有fputs则不能输出一些特殊字符，如\r \n
 */
int fputc(int _c, register FILE *_fp)
{
    //检验是否发送完毕，若未发送完毕，则进入循环等待发送完毕
    while(UART0->FR & 0x08);
    //发送数据
    UART0->DR = (uint8_t) _c;

    /*
     * 以下为UART库版本，若使用UART库则不需要再写fputs函数
     */
//    uint8_t input[1];
//    input[0] = _c;
//    UART_write(uartHandle, input, 1);

    return _c;
}

int fputs(const char *_ptr, register FILE *_fp)
{
    uint16_t i, len;
    len = strlen(_ptr);
    for (i = 0; i < len; i++)
    {
        while(UART0->FR & 0x08);
        UART0->DR = (uint8_t) _ptr[i];
    }
    return len;
}
/*****************************************************************************************/
