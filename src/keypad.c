#include "keypad.h"
#include <stdio.h>

/* This is used for testing, should be deleted when passing to production code*/
typedef struct output{
    uint8_t c1, c2, c3, c4;
}simulatedOutput;

simulatedKeypad keypad_4x4;
simulatedOutput colum_output;


/*-------------------Private defines---------------------*/

#define PIN_OUTPUT_HIGH 1
#define PIN_OUTPUT_LOW 0
#define PIN_MODE_OUTPUT 1
#define PIN_MODE_INPUT 2

/*------------------Private functions--------------------*/

/*Wrapper functions, whats inside should be replaced by your vendor HAL*/
static void _pin_set_mode(GPIO_TypeDef port, uint16_t pin, uint8_t mode)
{
    colum_output.c1 = 0;
    colum_output.c2 = 0;
    colum_output.c3 = 0;
    colum_output.c4 = 0;
}

static uint8_t _pin_read_input(GPIO_TypeDef port, uint16_t pin)
{
    /*This logic is a simulation of what the input should be when physically pressing a key
      should be replaced by your HAL read GPIO function*/
    if (keypad_4x4.flag1 == 1 && pin == R1_PIN && colum_output.c1 == 1) return 1;
    else if (keypad_4x4.flag2 == 1 && pin == R1_PIN && port == R1_PORT && colum_output.c2 == 1) return 1;
    else if (keypad_4x4.flag3 == 1 && pin == R1_PIN && port == R1_PORT && colum_output.c3 == 1) return 1;
    else if (keypad_4x4.flagA == 1 && pin == R1_PIN && port == R1_PORT && colum_output.c4 == 1) return 1;

    else if (keypad_4x4.flag4 == 1 && pin == R2_PIN && port == R2_PORT && colum_output.c1 == 1) return 1;
    else if (keypad_4x4.flag5 == 1 && pin == R2_PIN && port == R2_PORT && colum_output.c2 == 1) return 1;
    else if (keypad_4x4.flag6 == 1 && pin == R2_PIN && port == R2_PORT && colum_output.c3 == 1) return 1;
    else if (keypad_4x4.flagB == 1 && pin == R2_PIN && port == R2_PORT && colum_output.c4 == 1) return 1;

    else if (keypad_4x4.flag7 == 1 && pin == R3_PIN && port == R3_PORT && colum_output.c1 == 1) return 1;
    else if (keypad_4x4.flag8 == 1 && pin == R3_PIN && port == R3_PORT && colum_output.c2 == 1) return 1;
    else if (keypad_4x4.flag9 == 1 && pin == R3_PIN && port == R3_PORT && colum_output.c3 == 1) return 1;
    else if (keypad_4x4.flagC == 1 && pin == R3_PIN && port == R3_PORT && colum_output.c4 == 1) return 1;

    else if (keypad_4x4.flagAst == 1 && pin == R4_PIN && port == R4_PORT && colum_output.c1 == 1) return 1;
    else if (keypad_4x4.flag0 == 1 && pin == R4_PIN && port == R4_PORT && colum_output.c2 == 1) return 1;
    else if (keypad_4x4.flagHash == 1 && pin == R4_PIN && port == R4_PORT && colum_output.c3 == 1) return 1;
    else if (keypad_4x4.flagD == 1 && pin == R4_PIN && port == R4_PORT && colum_output.c4 == 1) return 1;
    else return 0;
}

static void _pin_write_output(GPIO_TypeDef port, uint16_t pin, uint8_t val)
{
    /*This logic is a simulation of what the output should be when writing to a GPIO,
    it should be replaced by your HAL write GPIO function*/
    if (val == PIN_OUTPUT_HIGH)
    {
        if (pin == C1_PIN && port == C1_PORT)
        {
            colum_output.c1 = 1;
        } 
        else if (pin == C2_PIN && port == C2_PORT)
        {
            colum_output.c2 = 1;
        } 
        else if (pin == C3_PIN && port == C3_PORT)
        {
            colum_output.c3 = 1;
        }
        else if (pin == C4_PIN && port == C4_PORT)
        {
            colum_output.c4 = 1;
        }
    }
    else if (val == PIN_OUTPUT_LOW) 
    {
        if (pin == C1_PIN && port == C1_PORT)
        {
            colum_output.c1 = 0;
        } 
        else if (pin == C2_PIN && port == C2_PORT)
        {
            colum_output.c2 = 0;
        } 
        else if (pin == C3_PIN && port == C3_PORT)
        {
            colum_output.c3 = 0;
        }
        else if (pin == C4_PIN && port == C4_PORT)
        {
            colum_output.c4 = 0;
        }
    }
}

static void _test_key_status(keypadPinout * myKeypad, GPIO_TypeDef columnPort, uint16_t columnPin, GPIO_TypeDef rowPort, uint16_t rowPin, uint8_t * flag)
{
    _pin_write_output(columnPort, columnPin, PIN_OUTPUT_HIGH);
    if(_pin_read_input(rowPort, rowPin)) 
        *flag = 1;
    _pin_write_output(columnPort, columnPin, PIN_OUTPUT_LOW);
}

/*@brief outputs 1 to a column, then checks row by row if a input is high, then outputs 0. Updates the value of a flag if a input was 1*/
//
static void _test_column(keypadPinout * myKeypad, GPIO_TypeDef port, uint16_t pin, char * key, uint8_t * flag)
{   
    /*Write 1 to the column pins*/
    _pin_write_output(port, pin, PIN_OUTPUT_HIGH);

    /*Read every row sequentially*/
    if (_pin_read_input(myKeypad -> r1Port, myKeypad -> r1Pin))
    {
        if (port == myKeypad -> c1Port && pin == myKeypad -> c1Pin) *key = '1';
        else if (port == myKeypad -> c2Port && pin == myKeypad -> c2Pin) *key = '2';
        else if (port == myKeypad -> c3Port && pin == myKeypad -> c3Pin) *key = '3';
        else if (port == myKeypad -> c4Port && pin == myKeypad -> c4Pin) *key = 'A';
        
        *flag = 1;
    }
    else if (_pin_read_input(myKeypad -> r2Port, myKeypad -> r2Pin))
    {
        if (port == myKeypad -> c1Port && pin == myKeypad -> c1Pin) *key = '4';
        else if (port == myKeypad -> c2Port && pin == myKeypad -> c2Pin) *key = '5';
        else if (port == myKeypad -> c3Port && pin == myKeypad -> c3Pin) *key = '6';
        else if (port == myKeypad -> c4Port && pin == myKeypad -> c4Pin) *key = 'B';

        *flag = 1;
    }
    else if (_pin_read_input(myKeypad -> r3Port, myKeypad -> r3Pin))
    {
        if (port == myKeypad -> c1Port && pin == myKeypad -> c1Pin) *key = '7';
        else if (port == myKeypad -> c2Port && pin == myKeypad -> c2Pin) *key = '8';
        else if (port == myKeypad -> c3Port && pin == myKeypad -> c3Pin) *key = '9';
        else if (port == myKeypad -> c4Port && pin == myKeypad -> c4Pin) *key = 'C';

        *flag = 1;
    }
    else if (_pin_read_input(myKeypad -> r4Port, myKeypad -> r4Pin))
    {
        if (port == myKeypad -> c1Port && pin == myKeypad -> c1Pin) *key = '*';
        else if (port == myKeypad -> c2Port && pin == myKeypad -> c2Pin) *key = '0';
        else if (port == myKeypad -> c3Port && pin == myKeypad -> c3Pin) *key = '#';
        else if (port == myKeypad -> c4Port && pin == myKeypad -> c4Pin) *key = 'D';

        *flag = 1;
    }
    _pin_write_output(port, pin, PIN_OUTPUT_LOW);
}

static char _keypad_read_rows(keypadPinout * myKeypad)
{
    char  key;
    uint8_t charDetected = 0;

    while(!charDetected)
    {
      _test_column(myKeypad, myKeypad -> c1Port, myKeypad -> c1Pin, &key, &charDetected);
      if(charDetected) break;
      _test_column(myKeypad, myKeypad -> c2Port, myKeypad -> c2Pin, &key, &charDetected);
      if(charDetected) break;
      _test_column(myKeypad, myKeypad -> c3Port, myKeypad -> c3Pin, &key, &charDetected);
      if(charDetected) break;
      _test_column(myKeypad, myKeypad -> c4Port, myKeypad -> c4Pin, &key, &charDetected);        
    }

    return key;
}

/*------------------Public functions--------------------*/

/* @brief initializes the keypad class instance
 * @param myKeypad is a pointer to the keypadPinout structure
*/
void keypad_init(keypadPinout * myKeypad)
{
    /*declare ports and pins*/
    myKeypad -> r1Port = R1_PORT; myKeypad -> r1Pin = R1_PIN;
    myKeypad -> r2Port = R2_PORT; myKeypad -> r2Pin = R2_PIN;
    myKeypad -> r3Port = R3_PORT; myKeypad -> r3Pin = R3_PIN;
    myKeypad -> r4Port = R4_PORT; myKeypad -> r4Pin = R4_PIN;
    myKeypad -> c1Port = C1_PORT; myKeypad -> c1Pin = C1_PIN;
    myKeypad -> c2Port = C2_PORT; myKeypad -> c2Pin = C2_PIN;
    myKeypad -> c3Port = C3_PORT; myKeypad -> c3Pin = C3_PIN;
    myKeypad -> c4Port = C4_PORT; myKeypad -> c4Pin = C4_PIN;

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


/* @brief Blocks the call untill a key is pressed
 * @param myKeypad is a pointer to the keypadPinout structure
 * @retval key that was pressed
*/
char keypad_detect_key(keypadPinout * myKeypad)
{
    char key;
    key = _keypad_read_rows(myKeypad);
    return key;
}

/* @brief Checks if the key is pressed or not
 * @param myKeypad is a pointer to the keypadPinout structure
 * @param key is a pointer to a character representing the key that we want to check its status
 * @retval 1 if key was pressed
 * @retval 0 if key was not pressed
*/
uint8_t keypad_check_status_key(keypadPinout * myKeypad, char * key)
{
    uint8_t flag = 0;
    switch(*key)
    {
        case '1':
            _test_key_status(myKeypad, myKeypad -> c1Port, myKeypad -> c1Pin, myKeypad -> r1Port, myKeypad -> r1Pin, &flag);
            break;
        case '2':
            _test_key_status(myKeypad, myKeypad -> c2Port, myKeypad -> c2Pin, myKeypad -> r1Port, myKeypad -> r1Pin, &flag);
            break;
        case '3':
            _test_key_status(myKeypad, myKeypad -> c3Port, myKeypad -> c3Pin, myKeypad -> r3Port, myKeypad -> r3Pin, &flag);
            break;
        case '4':
            _test_key_status(myKeypad, myKeypad -> c1Port, myKeypad -> c1Pin, myKeypad -> r2Port, myKeypad -> r2Pin, &flag);
            break;
        case '5':
            _test_key_status(myKeypad, myKeypad -> c2Port, myKeypad -> c2Pin, myKeypad -> r2Port, myKeypad -> r2Pin, &flag);
            break;
        case '6':
            _test_key_status(myKeypad, myKeypad -> c3Port, myKeypad -> c3Pin, myKeypad -> r2Port, myKeypad -> r2Pin, &flag);
            break;
        case '7':
            _test_key_status(myKeypad, myKeypad -> c1Port, myKeypad -> c1Pin, myKeypad -> r3Port, myKeypad -> r3Pin, &flag);
            break;
        case '8':
            _test_key_status(myKeypad, myKeypad -> c2Port, myKeypad -> c2Pin, myKeypad -> r3Port, myKeypad -> r3Pin, &flag);
            break;
        case '9':
            _test_key_status(myKeypad, myKeypad -> c3Port, myKeypad -> c3Pin, myKeypad -> r3Port, myKeypad -> r3Pin, &flag);
            break;
        case '0':
            _test_key_status(myKeypad, myKeypad -> c2Port, myKeypad -> c2Pin, myKeypad -> r4Port, myKeypad -> r4Pin, &flag);    
            break;
        case 'A':
            _test_key_status(myKeypad, myKeypad -> c4Port, myKeypad -> c4Pin, myKeypad -> r1Port, myKeypad -> r1Pin, &flag);
            break;
        case 'B':
            _test_key_status(myKeypad, myKeypad -> c4Port, myKeypad -> c4Pin, myKeypad -> r2Port, myKeypad -> r2Pin, &flag);
            break;
        case 'C':
            _test_key_status(myKeypad, myKeypad -> c4Port, myKeypad -> c4Pin, myKeypad -> r3Port, myKeypad -> r3Pin, &flag);
            break;
        case 'D':
            _test_key_status(myKeypad, myKeypad -> c4Port, myKeypad -> c4Pin, myKeypad -> r4Port, myKeypad -> r4Pin, &flag);
            break;
        case '*':
            _test_key_status(myKeypad, myKeypad -> c1Port, myKeypad -> c1Pin, myKeypad -> r4Port, myKeypad -> r4Pin, &flag);
            break;
        case '#':
            _test_key_status(myKeypad, myKeypad -> c3Port, myKeypad -> c3Pin, myKeypad -> r4Port, myKeypad -> r4Pin, &flag);
            break;
        default:
            break;
    }
    return flag;
}