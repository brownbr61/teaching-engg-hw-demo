# Assignment - Write `GPIO_Init`

- Modify `GPIO_Init` in gpio.c such that the tests in test.c pass
- Modes to Enable:
  - `GPIO_MODE_OUTPUT_PP`
  - `GPIO_MODE_INPUT`
- Implement _all_ drain types:
  - `GPIO_PULLUP`
  - `GPIO_PULLDOWN`
  - `GPIO_NOPULL`
- Make sure to implement _all_ speeds:
  - `GPIO_SPEED_FREQ_LOW`
  - `GPIO_SPEED_FREQ_MEDIUM`
  - `GPIO_SPEED_FREQ_HIGH`
- Don't worry about Alternate Function (`GPIO_Init->Alternate`) for now
- _Make sure to enable variable GPIO pins_

(as of right now, master_gpio.c is not in binary form; when given to students, master_gpio.c will be in binary form to prohibit cheating)

1. Find `GPIO_Init` in gpio.c
2. Refer to the reference manual to determine the changes that need to be made to `GPIO_Init(\*,\*)` in order to enable the pins as instructed above
