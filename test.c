#include "gpio.c"
#include "error.h"
#include "master_gpio.c"

#include <stdint.h>
#include <iostream>

void TEST_ASSERT_TRUE_MESSAGE(char val, const char* msg)
{
  if(val)
    return;
  std::cout << msg << std::endl;
  exit(1);
}
void test_pin(GPIO_InitTypeDef GPIO_InitStruct);


void test_01_startGPIO() {
  test_pin({GPIO_PIN_5,GPIO_MODE_OUTPUT_PP,GPIO_PULLUP,GPIO_SPEED_FREQ_LOW,0});
  std::cout << "pin_5 PASSED\n";
  test_pin({GPIO_PIN_2,GPIO_MODE_OUTPUT_PP,GPIO_PULLDOWN,GPIO_SPEED_FREQ_HIGH,0});
  std::cout << "pin_2 PASSED\n";
  test_pin({GPIO_PIN_3,GPIO_MODE_INPUT,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH,0});
  std::cout << "pin_3 PASSED\n";
}

void test_pin(GPIO_InitTypeDef GPIO_InitStruct) {
  HAL_StatusTypeDef error;

  GPIO_TypeDef GPIOY = {0,0,0,0,0,0,0,0,{0,0}};
  GPIO_TypeDef GPIOZ = {0,0,0,0,0,0,0,0,{0,0}};
  // GPIO_InitTypeDef GPIO_InitStruct = {GPIO_PIN_5,GPIO_MODE_OUTPUT_PP,GPIO_PULLUP,GPIO_SPEED_FREQ_LOW,0};

  error = GPIO_Init(&GPIOZ, &GPIO_InitStruct);
  HAL_GPIO_Init(&GPIOY, &GPIO_InitStruct);

  TEST_ASSERT_TRUE_MESSAGE(error == 0, "Make sure to implement GPIO_Init, you silly goose!");
  TEST_ASSERT_TRUE_MESSAGE(GPIOZ.MODER == GPIOY.MODER,"Incorrect bit assignment to gpio.MODER");
  TEST_ASSERT_TRUE_MESSAGE(GPIOZ.OTYPER == GPIOY.OTYPER,"Incorrect bit assignment to gpio.OTYPER");
  TEST_ASSERT_TRUE_MESSAGE(GPIOZ.OSPEEDR == GPIOY.OSPEEDR,"Incorrect bit assignment to gpio.OSPEEDR");
  TEST_ASSERT_TRUE_MESSAGE(GPIOZ.PUPDR == GPIOY.PUPDR,"Incorrect bit assignment to gpio.PUPDR");
}

int main() {

  test_01_startGPIO();
  return 0;
}