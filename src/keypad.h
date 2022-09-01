#include "stm32f4xx_hal_gpio.h"
#include <stdint.h>

/* This is used for testing, should be deleted when passing to production code*/
typedef struct keypad{
    uint8_t flag1, flag2, flag3, flag4, flag5, flag6, flag7, flag8, flag9, flag0, flagA, flagB,
    flagC, flagD, flagAst, flagHash;
}simulatedKeypad;

/*TODO: Find a better way for the user to specify the pins the keypad is connected*/
#define R1_PIN GPIO_PIN_0
#define R1_PORT GPIOA
#define R2_PIN GPIO_PIN_1
#define R2_PORT GPIOA
#define R3_PIN GPIO_PIN_0
#define R3_PORT GPIOB
#define R4_PIN GPIO_PIN_1
#define R4_PORT GPIOB
#define C1_PIN GPIO_PIN_0
#define C1_PORT GPIOC
#define C2_PIN GPIO_PIN_1
#define C2_PORT GPIOC
#define C3_PIN GPIO_PIN_0
#define C3_PORT GPIOD
#define C4_PIN GPIO_PIN_1
#define C4_PORT GPIOD

typedef struct keypadPins{
    GPIO_TypeDef r1Port; uint16_t r1Pin;
    GPIO_TypeDef r2Port; uint16_t r2Pin;
    GPIO_TypeDef r3Port; uint16_t r3Pin;
    GPIO_TypeDef r4Port; uint16_t r4Pin;
    GPIO_TypeDef c1Port; uint16_t c1Pin;
    GPIO_TypeDef c2Port; uint16_t c2Pin;
    GPIO_TypeDef c3Port; uint16_t c3Pin;
    GPIO_TypeDef c4Port; uint16_t c4Pin;
}keypadPinout;

void keypad_init(keypadPinout * myKeypad);
char keypad_detect_key(keypadPinout * myKeypad);
uint8_t keypad_check_password(char * pass);
uint8_t keypad_check_status_key(keypadPinout * myKeypad, char * key);