/**
 * @author [Petr Oblouk]
 * @github [https://github.com/peoblouk]
 * @create date 15-04-2022 - 16:46:28
 * @modify date 19-04-2022 - 19:24:41
 * @desc [description]
 */
#include "stm8s.h"
#include <stdio.h>

void main(void)
{
    GPIO_DeInit;
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // FREQ MCU 16MHz
    GPIO_Init(GPIOC, PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW); // PC5
    Serial.begin(9600);

    while (1)
    {
        GPIO_WriteReverse(GPIOC, PIN_5);
        printf("test\n");
        delay.ms(1000);
    }
}