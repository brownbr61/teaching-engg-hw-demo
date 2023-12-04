/**
  ******************************************************************************
  * @file    stm32f4xx_hal_gpio.c
  * @author  MCD Application Team
  * @brief   GPIO HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the General Purpose Input/Output (GPIO) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *
  @verbatim
  ==============================================================================
                    ##### GPIO Peripheral features #####
  ==============================================================================
  [..] 
  Subject to the specific hardware characteristics of each I/O port listed in the datasheet, each
  port bit of the General Purpose IO (GPIO) Ports, can be individually configured by software
  in several modes:
  (+) Input mode 
  (+) Analog mode
  (+) Output mode
  (+) Alternate function mode
  (+) External interrupt/event lines

  [..]  
  During and just after reset, the alternate functions and external interrupt  
  lines are not active and the I/O ports are configured in input floating mode.
  
  [..]   
  All GPIO pins have weak internal pull-up and pull-down resistors, which can be 
  activated or not.

  [..]
  In Output or Alternate mode, each IO can be configured on open-drain or push-pull
  type and the IO speed can be selected depending on the VDD value.

  [..]  
  All ports have external interrupt/event capability. To use external interrupt 
  lines, the port must be configured in input mode. All available GPIO pins are 
  connected to the 16 external interrupt/event lines from EXTI0 to EXTI15.
  
  [..]
  The external interrupt/event controller consists of up to 23 edge detectors 
  (16 lines are connected to GPIO) for generating event/interrupt requests (each 
  input line can be independently configured to select the type (interrupt or event) 
  and the corresponding trigger event (rising or falling or both). Each line can 
  also be masked independently. 

                     ##### How to use this driver #####
  ==============================================================================  
  [..]
    (#) Enable the GPIO AHB clock using the following function: __HAL_RCC_GPIOx_CLK_ENABLE(). 

    (#) Configure the GPIO pin(s) using HAL_GPIO_Init().
        (++) Configure the IO mode using "Mode" member from GPIO_InitTypeDef structure
        (++) Activate Pull-up, Pull-down resistor using "Pull" member from GPIO_InitTypeDef 
             structure.
        (++) In case of Output or alternate function mode selection: the speed is 
             configured through "Speed" member from GPIO_InitTypeDef structure.
        (++) In alternate mode is selection, the alternate function connected to the IO
             is configured through "Alternate" member from GPIO_InitTypeDef structure.
        (++) Analog mode is required when a pin is to be used as ADC channel 
             or DAC output.
        (++) In case of external interrupt/event selection the "Mode" member from 
             GPIO_InitTypeDef structure select the type (interrupt or event) and 
             the corresponding trigger event (rising or falling or both).

    (#) In case of external interrupt/event mode selection, configure NVIC IRQ priority 
        mapped to the EXTI line using HAL_NVIC_SetPriority() and enable it using
        HAL_NVIC_EnableIRQ().
         
    (#) To get the level of a pin configured in input mode use HAL_GPIO_ReadPin().
            
    (#) To set/reset the level of a pin configured in output mode use 
        HAL_GPIO_WritePin()/HAL_GPIO_TogglePin().
    
    (#) To lock pin configuration until next reset use HAL_GPIO_LockPin().

                 
    (#) During and just after reset, the alternate functions are not 
        active and the GPIO pins are configured in input floating mode (except JTAG
        pins).
  
    (#) The LSE oscillator pins OSC32_IN and OSC32_OUT can be used as general purpose 
        (PC14 and PC15, respectively) when the LSE oscillator is off. The LSE has 
        priority over the GPIO function.
  
    (#) The HSE oscillator pins OSC_IN/OSC_OUT can be used as 
        general purpose PH0 and PH1, respectively, when the HSE oscillator is off. 
        The HSE has priority over the GPIO function.
  
  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "mock_hal.h"
#include "gpio.h"

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @defgroup GPIO GPIO
  * @brief GPIO HAL module driver
  * @{
  */

#define HAL_GPIO_MODULE_ENABLED
#ifdef HAL_GPIO_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup GPIO_Private_Constants GPIO Private Constants
  * @{
  */

/**
  * @}
  */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup GPIO_Exported_Functions GPIO Exported Functions
  * @{
  */

/** @defgroup GPIO_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim    
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
  [..]
    This section provides functions allowing to initialize and de-initialize the GPIOs
    to be ready for use.
 
@endverbatim
  * @{
  */


/**
  * @brief  Initializes the GPIOx peripheral according to the specified parameters in the GPIO_Init.
  * @param  GPIOx where x can be (A..K) to select the GPIO peripheral for STM32F429X device or
  *                      x can be (A..I) to select the GPIO peripheral for STM32F40XX and STM32F427X devices.
  * @param  GPIO_Init pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval None
  */
HAL_StatusTypeDef GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
  if (GPIO_Init->Pin == 0) // Silly goose! We need a PIN!
    return HAL_INCOMPLETE;
  if (GPIO_Init->Mode > 0x1) // we only care about MODE_INPUT & MODE_OUTPUT
    return HAL_ERROR;
  if (GPIO_Init->Alternate != 0)
    return HAL_ERROR;

  char pinNumber = 0;

  while (GPIO_Init->Pin) {
    if (!(GPIO_Init->Pin & 0x1)) { // If not requested, don't enable
      GPIO_Init->Pin  = GPIO_Init->Pin >> 1;
      pinNumber++;
      continue;
    }

    GPIOx->MODER      |= (((GPIO_Init->Mode  & 0x3) << (pinNumber*2)) 
                          | ((GPIOx->MODER   & 0x3) << (pinNumber*2)));
    GPIOx->PUPDR      |= ((GPIO_Init->Pull   & 0x3) << (pinNumber*2)) 
                          | ((GPIOx->PUPDR   & 0x3) << (pinNumber*2));
    if(GPIO_Init->Mode & GPIO_MODE != MODE_INPUT)
      GPIOx->OSPEEDR  |= ((GPIO_Init->Speed  & 0x3) << (pinNumber*2))
                          | ((GPIOx->OSPEEDR & 0x3) << (pinNumber*2));

    GPIO_Init->Pin  = GPIO_Init->Pin >> 1; // prepare for next loop
    pinNumber++; // prepare for next loop
  }

  return HAL_OK;
}

/**
  * @brief  De-initializes the GPIOx peripheral registers to their default reset values.
  * @param  GPIOx where x can be (A..K) to select the GPIO peripheral for STM32F429X device or
  *                      x can be (A..I) to select the GPIO peripheral for STM32F40XX and STM32F427X devices.
  * @param  GPIO_Pin specifies the port bit to be written.
  *          This parameter can be one of GPIO_PIN_x where x can be (0..15).
  * @retval None
  */
void GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{}

/**
  * @}
  */

/** @defgroup GPIO_Exported_Functions_Group2 IO operation functions 
  *  @brief   GPIO Read and Write
  *
@verbatim
 ===============================================================================
                       ##### IO operation functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx where x can be (A..K) to select the GPIO peripheral for STM32F429X device or
  *                      x can be (A..I) to select the GPIO peripheral for STM32F40XX and STM32F427X devices.
  * @param  GPIO_Pin specifies the port bit to read.
  *         This parameter can be GPIO_PIN_x where x can be (0..15).
  * @retval The input port pin value.
  */
GPIO_PinState GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  return GPIO_PIN_SET;
}

/**
  * @brief  Sets or clears the selected data port bit.
  *
  * @note   This function uses GPIOx_BSRR register to allow atomic read/modify
  *         accesses. In this way, there is no risk of an IRQ occurring between
  *         the read and the modify access.
  *
  * @param  GPIOx where x can be (A..K) to select the GPIO peripheral for STM32F429X device or
  *                      x can be (A..I) to select the GPIO peripheral for STM32F40XX and STM32F427X devices.
  * @param  GPIO_Pin specifies the port bit to be written.
  *          This parameter can be one of GPIO_PIN_x where x can be (0..15).
  * @param  PinState specifies the value to be written to the selected bit.
  *          This parameter can be one of the GPIO_PinState enum values:
  *            @arg GPIO_PIN_RESET: to clear the port pin
  *            @arg GPIO_PIN_SET: to set the port pin
  * @retval None
  */
void GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{}

/**
  * @brief  Toggles the specified GPIO pins.
  * @param  GPIOx Where x can be (A..K) to select the GPIO peripheral for STM32F429X device or
  *                      x can be (A..I) to select the GPIO peripheral for STM32F40XX and STM32F427X devices.
  * @param  GPIO_Pin Specifies the pins to be toggled.
  * @retval None
  */
void GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{}

/**
  * @brief  Locks GPIO Pins configuration registers.
  * @note   The locked registers are GPIOx_MODER, GPIOx_OTYPER, GPIOx_OSPEEDR,
  *         GPIOx_PUPDR, GPIOx_AFRL and GPIOx_AFRH.
  * @note   The configuration of the locked GPIO pins can no longer be modified
  *         until the next reset.
  * @param  GPIOx where x can be (A..F) to select the GPIO peripheral for STM32F4 family
  * @param  GPIO_Pin specifies the port bit to be locked.
  *         This parameter can be any combination of GPIO_PIN_x where x can be (0..15).
  * @retval None
  */
HAL_StatusTypeDef GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  return HAL_ERROR;
}

/**
  * @brief  This function handles EXTI interrupt request.
  * @param  GPIO_Pin Specifies the pins connected EXTI line
  * @retval None
  */
void GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)
{
  /* EXTI line interrupt detected */
  // if(__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != RESET)
  // {
  //   __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
  //   HAL_GPIO_EXTI_Callback(GPIO_Pin);
  // }
}

/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin Specifies the pins connected EXTI line
  * @retval None
  */
void GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  // UNUSED(GPIO_Pin);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
}

/**
  * @}
  */


/**
  * @}
  */

#endif /* HAL_GPIO_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


