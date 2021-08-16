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
#include <ti/drivers/GPIO.h>
#include <ti/drivers/apps/LED.h>
#include <ti/drivers/apps/Button.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/*********************************************GPIO.h***************************************************/
//
////按键中断回调函数
////当按键被按下时，会自动调用该函数，按键索引会自动成为该函数的参数
//void ButtonCallBackFxn(uint_least8_t index)
//{
//    //判断时哪一个按键被按下了
//    //Button0被按下则改变LED0状态
//    //Button1被按下则改变LED1状态
//    if (index == CONFIG_GPIO_0)
//    {
//        GPIO_toggle(CONFIG_LED_0_GPIO);
//    }
//    else if (index == CONFIG_GPIO_1)
//    {
//        GPIO_toggle(CONFIG_LED_1_GPIO);
//    }
//}
//
///*
// *  ======== mainThread ========
// */
//void* mainThread(void *arg0)
//{
//    GPIO_init();
//    //配置按键中断回调函数
//    GPIO_setCallback(CONFIG_GPIO_0, ButtonCallBackFxn);
//    GPIO_setCallback(CONFIG_GPIO_1, ButtonCallBackFxn);
//    //使能按键中断
//    GPIO_enableInt(CONFIG_GPIO_0);
//    GPIO_enableInt(CONFIG_GPIO_1);
//
//    return (NULL);
//}
/********************************************************************************************************/

/*********************************************Button.h***************************************************/

//先定义两种结构体为全局结构体，分别对应Button0、Button1和LED0、LED1
Button_Handle buttonHandle0;
Button_Handle buttonHandle1;
Button_Params buttonParams0;
Button_Params buttonParams1;

LED_Handle ledHandle0;
LED_Handle ledHandle1;
LED_Params ledParams0;
LED_Params ledParams1;

//按键中断回调函数，当按键被按下时，会自动调用该函数
//函数参数有两个，buttonHandle表示哪个端口产生的中断，buttonEvents表示按键按下的状态
void ButtonCallBackFxn(Button_Handle buttonHandle,
                       Button_EventMask buttonEvents)
{
    //首先判断是哪一个按键被按下了
    if (buttonHandle == buttonHandle0)
    {
        //接着判断是短按还是长按
        //若是短按则常亮，长按则闪烁
        if (buttonEvents & Button_EV_PRESSED)
        {
            //切换LED模式需要先停止闪烁，因为在闪烁状态下无法直接变成常亮
            LED_stopBlinking(ledHandle0);
            LED_setOn(ledHandle0, 50);
        }
        else if (buttonEvents & Button_EV_LONGPRESSED)
        {
            LED_startBlinking(ledHandle0, 200, LED_BLINK_FOREVER);
        }
    }
    else if (buttonHandle == buttonHandle1)
    {
        if (buttonEvents & Button_EV_PRESSED)
        {
            LED_stopBlinking(ledHandle1);
            LED_setOn(ledHandle1, 50);
        }
        else if (buttonEvents & Button_EV_LONGPRESSED)
        {
            LED_startBlinking(ledHandle1, 200, LED_BLINK_FOREVER);
        }
    }
}
/*
 *  ======== mainThread ========
 */
void* mainThread(void *arg0)
{
    //初始化结构体ledParams为默认状态
    LED_Params_init(&ledParams0);
    LED_Params_init(&ledParams1);
    ledHandle0 = LED_open(CONFIG_LED_0, &ledParams0);
    ledHandle1 = LED_open(CONFIG_LED_1, &ledParams1);

    //初始化按键
    Button_init();
    /*
     * 初始化按键参数：
    *  ------------------------------------------------------------------
    *  parameter        | value        | description              | unit
    *  -----------------|--------------|--------------------------|------------
    *  debounceDuration | 10           | debounce duration        | ms
    *  longPressDuration| 2000         | long press duration      | ms
    *  buttonEventMask  | 0xFF         | subscribed to all events | NA
    */
    Button_Params_init(&buttonParams0);
    Button_Params_init(&buttonParams1);
    buttonHandle0 = Button_open(CONFIG_BUTTON_0, ButtonCallBackFxn,
                                &buttonParams0);
    buttonHandle1 = Button_open(CONFIG_BUTTON_1, ButtonCallBackFxn,
                                &buttonParams1);

    return (NULL);
}
/********************************************************************************************************/
