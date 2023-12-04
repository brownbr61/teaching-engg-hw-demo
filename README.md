# Assignment - Write `GPIO_Init`

- Modify GPIO_Init in gpio.c such that the tests in test.c pass.

(as of right now, master_gpio.c is not in binary form; when given to students, master_gpio.c will be in binary form to prohibit cheating)

1. Find GPIO_Init in gpio.c
2. Refer to the reference manual to determine the changes that need to be made to GPIO_Init(\*,\*) in order to enable the pin 5 with the following information:
   - GPIO_PIN_5
   - Mode: Output pp
   - connection: pull up
   - clock speed: slow
3. Try to make the changes generalizable
