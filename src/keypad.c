#include "keypad.h"

/*Private functions*/
/*Wrapper function, whats inside should be replaced by your vendor HAL*/
void _pin_set_output(uint8_t val)
{

}

void _pin_set_mode(uint8_t mode)
{

}

/*Public functions*/
void keypad_init(keypadPinout * myKeypad)
{
    /*declare ports and pins*/
    myKeypad -> r1Port = R1_PIN; myKeypad -> r1Pin = R1_PORT;
    myKeypad -> r2Port = R2_PIN; myKeypad -> r2Pin = R2_PORT;
    myKeypad -> r3Port = R3_PIN; myKeypad -> r3Pin = R3_PORT;
    myKeypad -> r4Port = R4_PIN; myKeypad -> r4Pin = R4_PORT;
    myKeypad -> c1Port = C1_PIN; myKeypad -> c1Pin = C1_PORT;
    myKeypad -> c2Port = C2_PIN; myKeypad -> c2Pin = C2_PORT;
    myKeypad -> c3Port = C3_PIN; myKeypad -> c3Pin = C3_PORT;
    myKeypad -> c4Port = C4_PIN; myKeypad -> c4Pin = C4_PORT;

    /*declare rows as output*/

    /*declare columns as input*/
}

char keypad_detect_key(keypadPinout * myKeypad)
{
    char key;
    uint8_t flagDetected = 0;
    //while(!flagDetected)
    //{
    //}

    return key;
}