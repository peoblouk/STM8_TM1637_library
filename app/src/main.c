/**
 * @author [Petr Oblouk]
 * @github [https://github.com/peoblouk]
 * @create date 15-04-2022 - 16:46:28
 * @modify date 19-04-2022 - 19:24:41
 * @desc [description]
 */
#include "stm8s.h"
#include "stm8s_tm1637.h"

int hours = 0, min = 0, secs = 0;
char szTemp[8];

void main(void)
{
    GPIO_DeInit;
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // FREQ MCU 16MHz
    GPIO_Init(GPIOC, PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW); // PC5
    Serial.begin(9600);                                 // Serial monitor Baudrate = 9600
    // tm1637.init(GPIOB, PIN_0, GPIOB, PIN_1);            // inicialization of TM1637
    // tm1637.setbrightness(7);
    //
    while (1)
    {
        if (secs == 60)
        {
            secs = 0;
            min++;
        }
        if (min == 60)
        {
            min = 0;
            hours++;
        }
        if (hours == 24)
        {
            hours = 0;
        }
        if (secs & 1)
            sprintf(szTemp, "%02d:%02d", hours, min);
        else
            sprintf(szTemp, "%02d %02d", hours, min);
        tm1637.dgt(szTemp);
        secs++;
        delay.ms(1000);
    }
    // printf("%s \n", szTemp);
}