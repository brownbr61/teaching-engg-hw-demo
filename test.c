#include "gpio.c"
#include "error.h"
#include "master_gpio.c"

#include <stdint.h>
#include <iostream>

void TEST_ASSERT_EQ_MESSAGE(uint32_t expected, uint32_t actual, const char* msg)
{
  if(expected == actual)
    return;
  
  std::cout << msg << std::endl;
  std::cout << "expected: 0x" << std::hex << expected << std::endl;
  std::cout << "actual:   0x" << std::hex << actual   << std::endl;
  exit(1);
}
void test_pin(GPIO_InitTypeDef, GPIO_TypeDef*, GPIO_TypeDef*);


void test_01_startGPIO() {
  GPIO_TypeDef GPIOY = {0,0,0,0,0,0,0,0,{0,0}};
  GPIO_TypeDef GPIOZ = {0,0,0,0,0,0,0,0,{0,0}};

  test_pin({GPIO_PIN_5,GPIO_MODE_OUTPUT_PP,GPIO_PULLUP,GPIO_SPEED_FREQ_LOW,0}, &GPIOY, &GPIOZ);
  std::cout << "pin_5 PASSED\n";
  test_pin({GPIO_PIN_2,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_MEDIUM,0}, &GPIOY, &GPIOZ);
  std::cout << "pin_2 PASSED\n";
  test_pin({GPIO_PIN_3,GPIO_MODE_INPUT,GPIO_PULLDOWN,GPIO_SPEED_FREQ_HIGH,0}, &GPIOY, &GPIOZ);
  std::cout << "pin_3 PASSED\n";
}

void test_pin(GPIO_InitTypeDef GPIO_InitStruct, GPIO_TypeDef *GPIOY, GPIO_TypeDef *GPIOZ) {
  HAL_StatusTypeDef error;

  HAL_GPIO_Init(GPIOY, &GPIO_InitStruct);
  error = GPIO_Init(GPIOZ, &GPIO_InitStruct);

  TEST_ASSERT_EQ_MESSAGE(error, 0, "Make sure to implement GPIO_Init, you silly goose!");
  TEST_ASSERT_EQ_MESSAGE(GPIOY->MODER, GPIOZ->MODER,"Incorrect bit assignment to gpio->MODER");
  TEST_ASSERT_EQ_MESSAGE(GPIOY->OTYPER, GPIOZ->OTYPER,"Incorrect bit assignment to gpio->OTYPER");
  TEST_ASSERT_EQ_MESSAGE(GPIOY->OSPEEDR, GPIOZ->OSPEEDR,"Incorrect bit assignment to gpio->OSPEEDR");
  TEST_ASSERT_EQ_MESSAGE(GPIOY->PUPDR, GPIOZ->PUPDR,"Incorrect bit assignment to gpio->PUPDR");
}

int main() {

  test_01_startGPIO();
  return 0;
}