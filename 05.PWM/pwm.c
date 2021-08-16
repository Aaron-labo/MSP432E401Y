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
#include "MyLib/mylib.h"

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/PWM.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/******************************定义结构体********************************/
PWM_Handle pwmHandle;
PWM_Params pwmParams;
uint32_t   dutyValue;
uint8_t i = 0, flag = 0;
/***********************************************************************/

/********************其他函数(如参数初始化、回调函数)*********************/


/***********************************************************************/

/*
 *  ======== mainThread ========
 */
void* mainThread(void *arg0)
{
    //=================PWM初始化================
    PWM_init();
    PWM_Params_init(&pwmParams);
    pwmHandle = PWM_open(CONFIG_PWM_0, &pwmParams);
    if (pwmHandle == NULL) {
        // PWM_open() failed
        printf("PWM_open() failed!!!\r\n");
        while (1);
    }
    //==========================================

    //开启PWM
    PWM_start(pwmHandle);
    while (1)
    {
        if(i >= 100){
            flag = 1;
        }else if(i <= 0){
            flag = 0;
        }
        if(flag == 0){
            dutyValue = (uint32_t) ((uint64_t) PWM_DUTY_FRACTION_MAX * (++i) / 100);
        }else if(flag == 1){
            dutyValue = (uint32_t) ((uint64_t) PWM_DUTY_FRACTION_MAX * (--i) / 100);
        }
        //设置PWM占空比
        PWM_setDuty(pwmHandle, dutyValue);
        usleep(10000);
    }
}
