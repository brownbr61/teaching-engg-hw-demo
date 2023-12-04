#ifndef __GPIO_H
#define __GPIO_H

#include <stdint.h>

#include "error.h"
#include "mock_hal.h"

#ifndef GPIO_NUMBER
#define GPIO_NUMBER 16u
#endif

#define GPIO_OSPEEDER_OSPEEDR0           0x3ul
#define GPIO_OTYPER_OT_0                 0x1ul
#define GPIO_PUPDR_PUPDR0                0x3ul
#define GPIO_MODER_MODER0                0x3ul
#define __HAL_RCC_SYSCFG_CLK_ENABLE()


/** 
  * @brief GPIO Init structure definition  
  */ 
typedef struct
{
  uint32_t Pin;       /*!< Specifies the GPIO pins to be configured.
                           This parameter can be any value of @ref GPIO_pins_define */

  uint32_t Mode;      /*!< Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref GPIO_mode_define */

  uint32_t Pull;      /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                           This parameter can be a value of @ref GPIO_pull_define */

  uint32_t Speed;     /*!< Specifies the speed for the selected pins.
                           This parameter can be a value of @ref GPIO_speed_define */

  uint32_t Alternate;  /*!< Peripheral to be connected to the selected pins. 
                            This parameter can be a value of @ref GPIO_Alternate_function_selection */
}GPIO_InitTypeDef;

/** 
  * @brief  GPIO Bit SET and Bit RESET enumeration 
  */
typedef enum
{
  GPIO_PIN_RESET = 0,
  GPIO_PIN_SET
}GPIO_PinState;

/**
  * @brief  Initialize the GPIOx peripheral according to the specified parameters in the GPIO_Init.
  * @param  GPIOx where x can be (A..F) to select the GPIO peripheral for STM32F0 family
  * @param  GPIO_Init pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval Non-Zero on error
  */
HAL_StatusTypeDef startGPIO(GPIO_TypeDef *gpio, GPIO_InitTypeDef* gpio_init);
HAL_StatusTypeDef invertGPIO_A5();

#endif