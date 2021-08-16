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

/* Driver Header files */
#include <ti/drivers/apps/LED.h>

/* Driver configuration */
#include "ti_drivers_config.h"

void delay(uint32_t time)
{
    uint32_t i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 10000; j++)
            ;
}

/*********************************************GPIO.h***************************************************/
///*
// *  ======== mainThread ========
// */
//void* mainThread(void *arg0)
//{
//    //GPIO的初始化函数，无法看到内部的具体代码
//    //但是在GPIO具体操作之前都需要有这个函数
//    GPIO_init();
//
//    while (1)
//    {
//        //GPIO_toggle为取反函数，当前为1(亮)，则置0(暗)，反之亦然。
//        GPIO_toggle(CONFIG_LED_0_GPIO);
//        GPIO_toggle(CONFIG_LED_1_GPIO);
//        //GPIO_read用于读取当前状态值
//        //GPIO_write用于写入状态值
//        //下面的代码与GPIO_toggle作用相同，即将当前状态值取反并再次写入
//        GPIO_write(CONFIG_LED_2_GPIO, !GPIO_read(CONFIG_LED_2_GPIO));
//        GPIO_write(CONFIG_LED_3_GPIO, !GPIO_read(CONFIG_LED_3_GPIO));
//        delay(1000);
//    }
//}
/********************************************************************************************************/

/*********************************************LED.h******************************************************/
/*
 *  ======== mainThread ========
 */
//使用LED库实现
void* mainThread(void *arg0)
{
    //先定义两个结构体，LED库必用到，分别对应LED0、LED1、LED2和LED3
    LED_Handle ledHandle0;
    LED_Handle ledHandle1;
    LED_Handle ledHandle2;
    LED_Handle ledHandle3;
    LED_Params ledParams0;
    LED_Params ledParams1;
    LED_Params ledParams2;
    LED_Params ledParams3;

    //初始化结构体ledParams为默认
    LED_Params_init(&ledParams0);
    LED_Params_init(&ledParams1);
    //手动初始化ledParams2，LED2闪烁
    ledParams2.blinkPeriod = 500; // 闪烁周期
    ledParams2.setState = LED_STATE_BLINKING; // 打开LED2，并设置为闪烁状态
    //手动初始化ledParams3，LED3常亮
    ledParams3.setState = LED_STATE_ON; // 打开LED2，并设置为闪烁状态

    //初始化LED(注意不是让LED亮)，同时也是初始化ledHandle结构体的过程
    //换句话说，ledHandle0和LED0绑定，ledHandle1和LED1绑定
    ledHandle0 = LED_open(CONFIG_LED_0, &ledParams0);
    ledHandle1 = LED_open(CONFIG_LED_1, &ledParams1);
    ledHandle2 = LED_open(CONFIG_LED_2, &ledParams2);
    ledHandle3 = LED_open(CONFIG_LED_3, &ledParams3);

    //点亮LED0，常亮
    LED_setOn(ledHandle0, 50);
    //点亮LED1，以0.2s为周期闪烁
    LED_startBlinking(ledHandle1, 200, LED_BLINK_FOREVER);
    //点亮LED2和LED3(其实这句话可以省略，不过为了代码整齐性，我还是加上了)
    //LED2会按照ledParams2中的设置闪烁，LED3会按照ledParams3中的设置常亮
    LED_setOn(ledHandle2, 50);
    LED_setOn(ledHandle3, 50);

    return (NULL);
}
/********************************************************************************************************/
