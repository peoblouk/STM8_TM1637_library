/**
 * @author [Petr Oblouk]
 * @github [https://github.com/peoblouk]
 * @create date 27-04-2022 - 15:08:43
 * @modify date 27-04-2022 - 15:08:43
 * @desc [TM1637 library]
 */
/**
 * @author [Petr Oblouk]
 * @github [https://github.com/peoblouk]
 * @create date 17-04-2022 - 11:43:25
 * @modify date 21-04-2022 - 07:31:15
 * @desc [4 digit segment display library]
 */

/* Includes ------------------------------------------------------------------*/
// #include "stm8s.h"
#include "stm8s_tm1637.h"
// #include "stdio.h"

/** @addtogroup STM8S_StdPeriph_Driver
 * @{
 */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
 * @addtogroup HELPERS_Public_Functions
 * @{
 */

/* -------------------------------------------------------------------------------------------*/

#define CLOCK_DELAY 0

#define LOW 0
#define HIGH 1
/*--------------------------------------------------------------------------------------------*/
// Table which translates a digit into the segments
const unsigned char cDigit2Seg[] = {0x3f, 0x6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

/*--------------------------------------------------------------------------------------------*/
// Initialize tm1637 with the clock and data pins
void tm1637_init(GPIO_TypeDef *bClock, GPIO_Pin_TypeDef bClockP, GPIO_TypeDef *bData, GPIO_Pin_TypeDef bDataP)
{
	GPIO_TypeDef *bClockPort = bClock;
	GPIO_Pin_TypeDef bDataPort = bData;

	GPIO_TypeDef *bClockPin = bClockP;
	GPIO_Pin_TypeDef bDataPin = bDataP;

	GPIO_Init(bClockPort, bClockPin, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(bDataPort, bDataPin, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_WriteLow(bClockPort, bClockPin);
	GPIO_WriteLow(bDataPort, bDataPin);
}
//
GPIO_TypeDef *bClockPort = GPIOB;
GPIO_Pin_TypeDef bDataPort = GPIOB;
GPIO_TypeDef *bClockPin = PIN_0;
GPIO_Pin_TypeDef bDataPin = PIN_1;

void tm1637_init()
{
	GPIO_Init(bClockPort, bClockPin, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(bDataPort, bDataPin, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_WriteLow(bClockPort, bClockPin);
	GPIO_WriteLow(bDataPort, bDataPin);
}
/*--------------------------------------------------------------------------------------------*/
// Start wire transaction
void tm1637_Start(void)
{
	/*
	GPIO_Set_Pin_High(bDataPort, bDataPin);
	GPIO_Set_Pin_High(bClockPort, bClockPin);
	usleep(CLOCK_DELAY);
	GPIO_Set_Pin_Low(bDataPort, bDataPin);
	*/

	//
	GPIO_WriteHigh(bDataPort, bDataPin);
	GPIO_WriteHigh(bClockPort, bClockPin);
	delay.us(CLOCK_DELAY);
	GPIO_WriteLow(bDataPort, bDataPin);
}

/*--------------------------------------------------------------------------------------------*/
// Stop wire transaction
void tm1637Stop(void)
{
	/* // clock low
	GPIO_Set_Pin_Low(bClockPort, bClockPin);
	usleep(CLOCK_DELAY);
	// data low
	GPIO_Set_Pin_Low(bDataPort, bDataPin);
	usleep(CLOCK_DELAY);
	// clock high
	GPIO_Set_Pin_High(bClockPort, bClockPin);
	usleep(CLOCK_DELAY);
	// data high
	GPIO_Set_Pin_High(bDataPort, bDataPin); */

	// updated
	// clock low
	GPIO_WriteLow(bClockPort, bClockPin);
	delay.us(CLOCK_DELAY);
	// data low
	GPIO_WriteLow(bDataPort, bDataPin);
	delay.us(CLOCK_DELAY);
	// clock high
	GPIO_WriteHigh(bClockPort, bClockPin);
	delay.us(CLOCK_DELAY);
	// data high
	GPIO_WriteHigh(bDataPort, bDataPin);
}

/*--------------------------------------------------------------------------------------------*/
// Get data ack
uint8_t tm1637_get_ack(void)
{
	uint8_t bAck = 1;

	/* 	// read ack
		// clock to low
		GPIO_Set_Pin_Low(bClockPort, bClockPin);
		// data as input

		usleep(CLOCK_DELAY);

		// clock high
		GPIO_Set_Pin_High(bClockPort, bClockPin);
		usleep(CLOCK_DELAY);
		// clock to low
		GPIO_Set_Pin_Low(bClockPort, bClockPin); */

	// updated
	// clock to low
	GPIO_WriteLow(bClockPort, bClockPin);
	delay.us(CLOCK_DELAY);
	// clock high
	GPIO_WriteHigh(bClockPort, bClockPin);
	delay.us(CLOCK_DELAY);
	// clock to low
	GPIO_WriteLow(bClockPort, bClockPin);

	return bAck;
}

/*--------------------------------------------------------------------------------------------*/
// Write a uint8_t to the controller
void tm1637_write_byte(uint8_t b)
{
	uint8_t i;

	for (i = 0; i < 8; i++)
	{
		// updated
		// clock low
		GPIO_WriteLow(bClockPort, bClockPin);

		if (b & 1)
		{
			GPIO_WriteHigh(bClockPort, bClockPin);
		}
		else
		{
			GPIO_WriteLow(bClockPort, bClockPin);
		}

		delay.ms(CLOCK_DELAY);
		// clock high
		GPIO_WriteHigh(bClockPort, bClockPin);
		delay.ms(CLOCK_DELAY);
		b >>= 1;
	}
}

/*--------------------------------------------------------------------------------------------*/
// Write a sequence of unsigned chars to the controller
void tm1637_write(uint8_t pData, uint8_t bLen)
{
	uint8_t b, bAck;
	bAck = 1;
	tm1637Start();
	for (b = 0; b < bLen; b++)
	{
		tm1637WriteByte(pData[b]);
		bAck &= tm1637GetAck();
	}
	tm1637Stop();
}

/*--------------------------------------------------------------------------------------------*/
// Set brightness (0-8)
void tm1637_set_brightness(uint8_t b)
{
	uint8_t bControl;
	if (b == 0)
		// display off
		bControl = 0x80;
	else
	{
		if (b > 8)
			b = 8;
		bControl = 0x88 | (b - 1);
	}
	tm1637Write(&bControl, 1);
}

/*--------------------------------------------------------------------------------------------*/
// Display a string of 4 digits and optional colon
// by passing a string such as "12:34" or "45 67"
void tm1637_show_digits(char pString)
{
	// commands and data to transmit
	uint8_t b, bTemp[16];
	uint8_t i, j;
	j = 0;

	// memory write command (auto increment mode)
	bTemp[0] = 0x40;
	tm1637Write(bTemp, 1);

	// set display address to first digit command
	bTemp[j++] = 0xc0;
	for (i = 0; i < 5; i++)
	{
		// position of the colon
		if (i == 2)
		{
			// turn on correct bit
			if (pString[i] == ':')
			{
				// second digit high bit controls colon LEDs
				bTemp[2] |= 0x80;
			}
		}
		else
		{
			b = 0;
			if (pString[i] >= '0' && pString[i] <= '9')
			{
				// segment data
				b = cDigit2Seg[pString[i] & 0xf];
			}
			bTemp[j++] = b;
		}
	}
	// send to the display
	tm1637Write(bTemp, j);
}

/*--------------------------------------------------------------------------------------------*/
const TM1637_Module tm1637 = {
	.init = tm1637_init,
	.start = tm1637_start,
	.stop = tm1637_stop,
	.getack = tm1637_get_ack,
	.writebyte = tm1637_write_byte,
	.write = tm1637_write,
	.brightness = tm1637_set_brightness,
	.showdgt = tm1637_show_digits,
};
/* -------------------------------------------------------------------------------------------*/

/**
 * @}
 */

/*****************************END OF FILE****/
