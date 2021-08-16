/*
 * mylib.c
 *
 *  Created on: 2021年8月15日
 *      Author: Francis
 *
 *  主要包含printf重定向和延时函数
 *  其中printf使用的外设为UART0
 *  延时函数sleep()在unistd.h中
 */

/* Driver configuration */
#include "ti_drivers_config.h"
#include "mylib.h"

//printf重定向有关头文件
#include <string.h>
#include <ti/devices/msp432e4/inc/msp432e401y.h>
#include <ti/drivers/UART.h>


/***********************************定义结构体*****************************************/
//定义UART结构体，用于printf重定向
UART_Handle uartHandle;
UART_Params uartParams;
/*************************************************************************************/

/***********************************printf重定向***************************************/
/*
 * 添加下面两个函数可以实现printf重定向
 * 若只有fputc则不能输出格式化字符串，如%d %f
 * 若只有fputs则不能输出一些特殊字符，如\r \n
 */
int fputc(int _c, register FILE *_fp)
{
    //检验是否发送完毕，若未发送完毕，则进入循环等待发送完毕
    while (UART0->FR & 0x08)
        ;
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
        while (UART0->FR & 0x08)
            ;
        UART0->DR = (uint8_t) _ptr[i];
    }
    return len;
}
/**************************************************************************************/

void mainLib(void)
{
    //================UART初始化======================
    UART_init();
    UART_Params_init(&uartParams);
    uartHandle = UART_open(CONFIG_UART_0, &uartParams);
    if (uartHandle == NULL)
    {
        // UART_open() failed
        printf("UART_open() failed!!!\r\n");
        while (1)
            ;
    }
    //================================================
}
