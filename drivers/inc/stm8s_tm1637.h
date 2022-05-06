/**
 * @author [Petr Oblouk]
 * @github [https://github.com/peoblouk]
 * @create date 27-04-2022 - 18:57:25
 * @modify date 27-04-2022 - 18:57:25
 * @desc [TM1637 library]
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8S_TM1637_H
#define __STM8S_TM1637_H
/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Exported types ------------------------------------------------------------*/
/** @addtogroup HELPERS_Exported_Types
 * @{
 */
typedef struct
{
    // Initialize tm1637 with the clock and data pins
    void (*init_)(GPIO_TypeDef *, GPIO_Pin_TypeDef, GPIO_TypeDef *, GPIO_Pin_TypeDef);

    // Start wire transaction
    void (*start)(void);

    // Stop wire transaction
    void (*stop)(void);

    // Get data acknowledgement
    uint8_t (*getack)(void);

    // Write a unsigned char to the controller
    void (*writebyte)(uint8_t);

    // Write a sequence of unsigned chars to the controller
    void (*write)(uint8_t *, uint8_t);

    // Set brightness (0-8)
    void (*setbrightness)(uint8_t);

    // Display a string of 4 digits and optional colon
    // by passing a string such as "12:34" or "45 67"
    void (*dgt)(char *);
} TM1637_Module;

/*
// Initialize tm1637 with the clock and data pins

int tm1637Init(GPIO_TypeDef *bClock, GPIO_Pin_TypeDef bClockP, GPIO_TypeDef *bData, GPIO_Pin_TypeDef bDataP);

// Start wire transaction

 void tm1637Start(void);

// Stop wire transaction

 void tm1637Stop(void);

// Get data acknowledgement

 uint8_t tm1637GetAck(void);

// Write a unsigned char to the controller

 void tm1637WriteByte(uint8_t b);

// Write a sequence of unsigned chars to the controller

 void tm1637Write(uint8_t *pData, uint8_t bLen);

// Set brightness (0-8)

void tm1637SetBrightness(uint8_t b);

// Display a string of 4 digits and optional colon
// by passing a string such as "12:34" or "45 67"

void tm1637ShowDigits(char *pString);
*/

/**
 * @}
 */

/* Exported constants --------------------------------------------------------*/

/** @addtogroup HELPERS_Exported_Constants
 * @{
 */

/**
 * @}
 */

/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup HELPERS_Private_Macros
 * @{
 */

/**
 * @}
 */

/* Exported functions ------------------------------------------------------- */
/** @addtogroup HELPERS_Exported_Functions
 * @{
 */
void tm1637_init(GPIO_TypeDef *bClock, GPIO_Pin_TypeDef bClockP, GPIO_TypeDef *bData, GPIO_Pin_TypeDef bDataP);
void tm1637_start(void);
void tm1637_stop(void);
uint8_t tm1637_get_ack(void);
void tm1637_write_byte(uint8_t b);
void tm1637_write(uint8_t *pData, uint8_t bLen);
void tm1637_set_brightness(uint8_t b);
void tm1637_show_digits(char *pString);
extern const TM1637_Module tm1637;

#endif /* __STM8S_TM1637 */