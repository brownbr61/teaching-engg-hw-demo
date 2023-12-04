#ifndef __MOCK_HAL_H
#define __MOCK_HAL_H
#include <stdint.h>

/** 
  * @brief Reset and Clock Control
  */

typedef struct
{
  uint32_t CR;            /*!< RCC clock control register,                                   Address offset: 0x00 */
  uint32_t CFGR;       /*!< RCC clock configuration register,                            Address offset: 0x04 */
  uint32_t CIR;        /*!< RCC clock interrupt register,                                Address offset: 0x08 */
  uint32_t APB2RSTR;   /*!< RCC APB2 peripheral reset register,                          Address offset: 0x0C */
  uint32_t APB1RSTR;   /*!< RCC APB1 peripheral reset register,                          Address offset: 0x10 */
  uint32_t AHB1ENR;     /*!< RCC AHB peripheral clock register,                           Address offset: 0x14 */
  uint32_t APB2ENR;    /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x18 */
  uint32_t APB1ENR;    /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x1C */
  uint32_t BDCR;       /*!< RCC Backup domain control register,                          Address offset: 0x20 */
  uint32_t CSR;        /*!< RCC clock control & status register,                         Address offset: 0x24 */
  uint32_t AHBRSTR;    /*!< RCC AHB peripheral reset register,                           Address offset: 0x28 */
  uint32_t CFGR2;      /*!< RCC clock configuration register 2,                          Address offset: 0x2C */
  uint32_t CFGR3;      /*!< RCC clock configuration register 3,                          Address offset: 0x30 */
  uint32_t CR2;        /*!< RCC clock control register 2,                                Address offset: 0x34 */
} RCC_TypeDef;

/** 
  * @brief General Purpose I/O
  */

typedef struct
{
  uint32_t MODER;        /*!< GPIO port mode register,                     Address offset: 0x00      */
  uint32_t OTYPER;       /*!< GPIO port output type register,              Address offset: 0x04      */
  uint32_t OSPEEDR;      /*!< GPIO port output speed register,             Address offset: 0x08      */
  uint32_t PUPDR;        /*!< GPIO port pull-up/pull-down register,        Address offset: 0x0C      */
  uint32_t IDR;          /*!< GPIO port input data register,               Address offset: 0x10      */
  uint32_t ODR;          /*!< GPIO port output data register,              Address offset: 0x14      */
  uint32_t BSRR;         /*!< GPIO port bit set/reset register,      Address offset: 0x1A */
  uint32_t LCKR;         /*!< GPIO port configuration lock register,       Address offset: 0x1C      */
  uint32_t AFR[2];       /*!< GPIO alternate function low register,  Address offset: 0x20-0x24 */
  uint32_t BRR;          /*!< GPIO bit reset register,                     Address offset: 0x28      */
} GPIO_TypeDef;
  
/* Exported constants --------------------------------------------------------*/
/** @defgroup GPIO_Exported_Constants GPIO Exported Constants
  * @{
  */
/** @defgroup GPIO_pins GPIO pins
  * @{
  */
#define GPIO_PIN_0                 ((uint16_t)0x0001U)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002U)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004U)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008U)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010U)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020U)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040U)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080U)  /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint16_t)0x0100U)  /* Pin 8 selected    */
#define GPIO_PIN_9                 ((uint16_t)0x0200U)  /* Pin 9 selected    */
#define GPIO_PIN_10                ((uint16_t)0x0400U)  /* Pin 10 selected   */
#define GPIO_PIN_11                ((uint16_t)0x0800U)  /* Pin 11 selected   */
#define GPIO_PIN_12                ((uint16_t)0x1000U)  /* Pin 12 selected   */
#define GPIO_PIN_13                ((uint16_t)0x2000U)  /* Pin 13 selected   */
#define GPIO_PIN_14                ((uint16_t)0x4000U)  /* Pin 14 selected   */
#define GPIO_PIN_15                ((uint16_t)0x8000U)  /* Pin 15 selected   */
#define GPIO_PIN_All               ((uint16_t)0xFFFFU)  /* All pins selected */

#define GPIO_PIN_MASK              (0x0000FFFFU) /* PIN mask for assert test */
/**
  * @}
  */
/**
  * @}
  */ 
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup GPIO_Private_Constants GPIO Private Constants
  * @{
  */
#define GPIO_MODE_Pos                           0U
#define GPIO_MODE                               (0x3UL << GPIO_MODE_Pos)
#define MODE_INPUT                              (0x0UL << GPIO_MODE_Pos)
#define MODE_OUTPUT                             (0x1UL << GPIO_MODE_Pos)
#define MODE_AF                                 (0x2UL << GPIO_MODE_Pos)
#define MODE_ANALOG                             (0x3UL << GPIO_MODE_Pos)
#define OUTPUT_TYPE_Pos                         4U
#define OUTPUT_TYPE                             (0x1UL << OUTPUT_TYPE_Pos)
#define OUTPUT_PP                               (0x0UL << OUTPUT_TYPE_Pos)
#define OUTPUT_OD                               (0x1UL << OUTPUT_TYPE_Pos)
#define EXTI_MODE_Pos                           16U
#define EXTI_MODE                               (0x3UL << EXTI_MODE_Pos)
#define EXTI_IT                                 (0x1UL << EXTI_MODE_Pos)
#define EXTI_EVT                                (0x2UL << EXTI_MODE_Pos)
#define TRIGGER_MODE_Pos                         20U
#define TRIGGER_MODE                            (0x7UL << TRIGGER_MODE_Pos)
#define TRIGGER_RISING                          (0x1UL << TRIGGER_MODE_Pos)
#define TRIGGER_FALLING                         (0x2UL << TRIGGER_MODE_Pos)

/** @defgroup GPIO_mode GPIO mode
  * @brief GPIO Configuration Mode
  *        Elements values convention: 0x00WX00YZ
  *           - W  : EXTI trigger detection on 3 bits
  *           - X  : EXTI mode (IT or Event) on 2 bits
  *           - Y  : Output type (Push Pull or Open Drain) on 1 bit
  *           - Z  : GPIO mode (Input, Output, Alternate or Analog) on 2 bits
  * @{
  */ 
#define  GPIO_MODE_INPUT                        MODE_INPUT                                                  /*!< Input Floating Mode                   */
#define  GPIO_MODE_OUTPUT_PP                    (MODE_OUTPUT | OUTPUT_PP)                                   /*!< Output Push Pull Mode                 */
#define  GPIO_MODE_OUTPUT_OD                    (MODE_OUTPUT | OUTPUT_OD)                                   /*!< Output Open Drain Mode                */
#define  GPIO_MODE_AF_PP                        (MODE_AF | OUTPUT_PP)                                       /*!< Alternate Function Push Pull Mode     */
#define  GPIO_MODE_AF_OD                        (MODE_AF | OUTPUT_OD)                                       /*!< Alternate Function Open Drain Mode    */

#define  GPIO_MODE_ANALOG                       MODE_ANALOG                                                 /*!< Analog Mode  */
    
#define  GPIO_MODE_IT_RISING                    (MODE_INPUT | EXTI_IT | TRIGGER_RISING)                     /*!< External Interrupt Mode with Rising edge trigger detection          */
#define  GPIO_MODE_IT_FALLING                   (MODE_INPUT | EXTI_IT | TRIGGER_FALLING)                    /*!< External Interrupt Mode with Falling edge trigger detection         */
#define  GPIO_MODE_IT_RISING_FALLING            (MODE_INPUT | EXTI_IT | TRIGGER_RISING | TRIGGER_FALLING)   /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */
 
#define  GPIO_MODE_EVT_RISING                   (MODE_INPUT | EXTI_EVT | TRIGGER_RISING)                     /*!< External Event Mode with Rising edge trigger detection             */
#define  GPIO_MODE_EVT_FALLING                  (MODE_INPUT | EXTI_EVT | TRIGGER_FALLING)                    /*!< External Event Mode with Falling edge trigger detection            */
#define  GPIO_MODE_EVT_RISING_FALLING           (MODE_INPUT | EXTI_EVT | TRIGGER_RISING | TRIGGER_FALLING)   /*!< External Event Mode with Rising/Falling edge trigger detection     *//**
  * @}
  */
                                                         
/** @defgroup GPIO_speed GPIO speed
  * @brief GPIO Output Maximum frequency
  * @{
  */  
#define  GPIO_SPEED_FREQ_LOW      (0x00000000U)  /*!< range up to 2 MHz, please refer to the product datasheet */
#define  GPIO_SPEED_FREQ_MEDIUM   (0x00000001U)  /*!< range  4 MHz to 10 MHz, please refer to the product datasheet */
#define  GPIO_SPEED_FREQ_HIGH     (0x00000003U)  /*!< range 10 MHz to 50 MHz, please refer to the product datasheet */
/**
  * @}
  */

 /** @defgroup GPIO_pull GPIO pull
   * @brief GPIO Pull-Up or Pull-Down Activation
   * @{
   */  
#define  GPIO_NOPULL        (0x00000000U)   /*!< No Pull-up or Pull-down activation  */
#define  GPIO_PULLUP        (0x00000001U)   /*!< Pull-up activation                  */
#define  GPIO_PULLDOWN      (0x00000002U)   /*!< Pull-down activation                */
GPIO_TypeDef dummy;
GPIO_TypeDef* GPIOA = &dummy;

RCC_TypeDef RCCdata;
RCC_TypeDef* RCC = &RCCdata;
#define RCC_AHB1ENR_GPIOAEN_Pos                   (17U)                         
#define RCC_AHB1ENR_GPIOAEN_Msk                   (0x1UL << RCC_AHB1ENR_GPIOAEN_Pos) /*!< 0x00020000 */
#define RCC_AHB1ENR_GPIOAEN                       RCC_AHB1ENR_GPIOAEN_Msk        /*!< GPIOA clock enable */

#endif