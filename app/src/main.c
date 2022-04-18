/**
 * @author [Petr Oblouk]
 * @github [https://github.com/peoblouk]
 * @create date 15-04-2022 - 16:46:28
 * @modify date 15-04-2022 - 23:23:31
 * @desc [description]
 */
#include "stm8s.h"

void setup(void)
{
    GPIO_DeInit;
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // FREQ MCU 16MHz
    GPIO_Init(GPIOC, PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW); // PC5
}

void loop(void)
{
    GPIO_WriteReverse(GPIOC, PIN_5);
    delay.ms(100);
}
