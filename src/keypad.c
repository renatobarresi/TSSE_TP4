#include "keypad.h"

#define PIN_OUTPUT_HIGH 1
#define PIN_OUTPUT_LOW 1
#define PIN_MODE_OUTPUT 1
#define PIN_MODE_INPUT 2

/*Private functions*/
/*Wrapper functions, whats inside should be replaced by your vendor HAL*/
void _pin_set_mode(GPIO_TypeDef port, uint16_t pin, uint8_t mode)
{

}

uint8_t _pin_read_input(GPIO_TypeDef port, uint16_t pin)
{

}

void _pin_write_output(GPIO_TypeDef port, uint16_t pin, uint8_t val)
{

}

void _test_column(keypadPinout * myKeypad, GPIO_TypeDef port, uint16_t pin, char * key, uint8_t * flag)
{
    _pin_write_output(port, pin, PIN_OUTPUT_HIGH);
    if (_pin_read_input(myKeypad -> r1Pin, myKeypad -> r1Port))
    {
        if (port == myKeypad -> c1Port && pin == myKeypad -> c1Pin) *key = '1';
        else if (port == myKeypad -> c2Port && pin == myKeypad -> c2Pin) *key = '2';
        else if (port == myKeypad -> c3Port && pin == myKeypad -> c3Pin) *key = '3';
        else if (port == myKeypad -> c4Port && pin == myKeypad -> c4Pin) *key = 'A';

        *flag = 1;
    }
    else if (_pin_read_input(myKeypad -> r2Pin, myKeypad -> r2Port))
    {
        if (port == myKeypad -> c1Port && pin == myKeypad -> c1Pin) *key = '4';
        else if (port == myKeypad -> c2Port && pin == myKeypad -> c2Pin) *key = '5';
        else if (port == myKeypad -> c3Port && pin == myKeypad -> c3Pin) *key = '6';
        else if (port == myKeypad -> c4Port && pin == myKeypad -> c4Pin) *key = 'B';
        *flag = 1;
    }
    else if (_pin_read_input(myKeypad -> r3Pin, myKeypad -> r3Port))
    {
        if (port == myKeypad -> c1Port && pin == myKeypad -> c1Pin) *key = '7';
        else if (port == myKeypad -> c2Port && pin == myKeypad -> c2Pin) *key = '8';
        else if (port == myKeypad -> c3Port && pin == myKeypad -> c3Pin) *key = '9';
        else if (port == myKeypad -> c4Port && pin == myKeypad -> c4Pin) *key = 'C';
        *flag = 1;
    }
    else if (_pin_read_input(myKeypad -> r4Pin, myKeypad -> r4Port))
    {
        if (port == myKeypad -> c1Port && pin == myKeypad -> c1Pin) *key = '*';
        else if (port == myKeypad -> c2Port && pin == myKeypad -> c2Pin) *key = '0';
        else if (port == myKeypad -> c3Port && pin == myKeypad -> c3Pin) *key = '#';
        else if (port == myKeypad -> c4Port && pin == myKeypad -> c4Pin) *key = 'D';
        *flag = 1;
    }
    _pin_write_output(port, pin, PIN_OUTPUT_LOW);
}

char _keypad_read_rows(keypadPinout * myKeypad)
{
    char  key;
    uint8_t charDetected = 0;
    uint8_t count = 0;

    while(!charDetected)
    {
      _test_column(myKeypad, myKeypad -> c1Port, myKeypad -> c1Pin, &key, &charDetected);
      _test_column(myKeypad, myKeypad -> c2Port, myKeypad -> c2Pin, &key, &charDetected);
      _test_column(myKeypad, myKeypad -> c3Port, myKeypad -> c3Pin, &key, &charDetected);
      _test_column(myKeypad, myKeypad -> c4Port, myKeypad -> c4Pin, &key, &charDetected);         
    }

    return key;
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

    /*declare Columns as output*/
    _pin_set_mode(myKeypad -> c1Port, myKeypad -> c1Pin, PIN_MODE_OUTPUT);
    _pin_set_mode(myKeypad -> c2Port, myKeypad -> c2Pin, PIN_MODE_OUTPUT);
    _pin_set_mode(myKeypad -> c3Port, myKeypad -> c3Pin, PIN_MODE_OUTPUT);
    _pin_set_mode(myKeypad -> c4Port, myKeypad -> c4Pin, PIN_MODE_OUTPUT);

    /*declare Rows as input*/
    _pin_set_mode(myKeypad -> r1Port, myKeypad -> r1Pin, PIN_MODE_INPUT);
    _pin_set_mode(myKeypad -> r2Port, myKeypad -> r2Pin, PIN_MODE_INPUT);
    _pin_set_mode(myKeypad -> r3Port, myKeypad -> r3Pin, PIN_MODE_INPUT);
    _pin_set_mode(myKeypad -> r4Port, myKeypad -> r4Pin, PIN_MODE_INPUT);
}

char keypad_detect_key(keypadPinout * myKeypad)
{
    char key;
    key = _keypad_read_rows(myKeypad);
    return key;
}