/*
    El modulo a testear es el de manejo de un keypad 4x4
    Los test a ejecutar son los siguientes:
    -Key presionada
    -Estado de una key
    -Testeo de deteccion de password correcto
    -Testeo de deteccion de password incorrecto
    -Cambio de estado de una key
    -Testeo de evento en base a secuencia de keys
*/

#include "unity.h"
#include "keypad.h"

/*---------------Simulaciones----------------*/

extern simulatedKeypad keypad_4x4;          //! simulation class instance

/*@brief we use flags to simulate the action of pressing the key*/
void simular_tecla_presionada(char tecla)
{
    switch(tecla)
    {
        case '1':
            keypad_4x4.flag1 = 1;
            break;
        case '2':
            keypad_4x4.flag2 = 1;
            break;
        case '3':
            keypad_4x4.flag3 = 1;
            break;
        case '4':
            keypad_4x4.flag4 = 1;
            break;
        case '5':
            keypad_4x4.flag5 = 1;
            break;
        case '6':
            keypad_4x4.flag6 = 1;
            break;
        case '7':
            keypad_4x4.flag7 = 1;
            break;
        case '8':
            keypad_4x4.flag8 = 1;
            break;
        case '9':
            keypad_4x4.flag9 = 1;
            break;
        case '0':
            keypad_4x4.flag0 = 1;
            break;
        case 'A':
            keypad_4x4.flagA = 1;
            break;
        case 'B':
            keypad_4x4.flagB = 1;
            break;
        case 'C':
            keypad_4x4.flagC = 1;
            break;
        case 'D':
            keypad_4x4.flagD = 1;
            break;
        case '*':
            keypad_4x4.flagAst = 1;
            break;
        case '#':
            keypad_4x4.flagHash = 1;
            break;
    }
}

void simulated_no_key_pressed(void)
{
    keypad_4x4.flag1 = 0, keypad_4x4.flag2 = 0, keypad_4x4.flag3 = 0, keypad_4x4.flag4 = 0, keypad_4x4.flag5 = 0, keypad_4x4.flag6 = 0, keypad_4x4.flag7 = 0, 
    keypad_4x4.flag8 = 0, keypad_4x4.flag9 = 0, keypad_4x4.flag0 = 0, keypad_4x4.flagA = 0, keypad_4x4.flagB = 0,
    keypad_4x4.flagC = 0, keypad_4x4.flagD = 0, keypad_4x4.flagAst = 0, keypad_4x4.flagHash = 0;
}

/*--------------Tests---------------*/

keypadPinout HC_543_Keypad;                //! keypadPinout class instance

/* @brief all keys are not pressed and inits the keypad */
void setUp(void)
{
    simulated_no_key_pressed();
    keypad_init(&HC_543_Keypad);
}

/* @brief check if a specific key is pressed */
void test_pressed_key_is_1(void)
{
    char key = '1';
    char pressedKey;
    simular_tecla_presionada(key);
    pressedKey = keypad_detect_key(&HC_543_Keypad);
    TEST_ASSERT_EQUAL(key, pressedKey);
}

/* @brief check if a specific key is pressed */
void test_pressed_key_is_B(void)
{
    char key = 'B';
    char pressedKey;
    simular_tecla_presionada(key);
    pressedKey = keypad_detect_key(&HC_543_Keypad);
    TEST_ASSERT_EQUAL(key, pressedKey);
}

/* @brief check if a specific key is pressed */
void test_pressed_key_is_hash(void)
{
    char key = '#';
    char pressedKey;
    simular_tecla_presionada(key);
    pressedKey = keypad_detect_key(&HC_543_Keypad);
    TEST_ASSERT_EQUAL(key, pressedKey);
}

/* @brief check if a specific key is pressed */
void test_pressed_key_is_6(void)
{
    char key = '6';
    char pressedKey;
    simular_tecla_presionada(key);
    pressedKey = keypad_detect_key(&HC_543_Keypad);
    TEST_ASSERT_EQUAL(key, pressedKey);
}

/* @brief check if a particular key is pressed */
void test_if_key_is_pressed(void)
{
    char key = '7';
    uint8_t keyStatus = 0;
    simular_tecla_presionada(key);
    keyStatus = keypad_check_status_key(&HC_543_Keypad, &key);
    TEST_ASSERT_EQUAL(1, keyStatus);
}

/* @brief check if a particular key is not pressed */
void test_if_key_not_pressed(void)
{
    char key = '7';
    uint8_t keyStatus = 0;
    keyStatus = keypad_check_status_key(&HC_543_Keypad, &key);
    TEST_ASSERT_EQUAL(0, keyStatus);
}

/* @brief check if a particular key is pressed */
void test_if_ast_key_is_pressed(void)
{
    char key = '*';
    uint8_t keyStatus = 0;
    simular_tecla_presionada(key);
    keyStatus = keypad_check_status_key(&HC_543_Keypad, &key);
    TEST_ASSERT_EQUAL(1, keyStatus);
}

/* @brief check if a particular key is not pressed */
void test_if_ast_key_not_pressed(void)
{
    char key = '*';
    uint8_t keyStatus = 0;
    keyStatus = keypad_check_status_key(&HC_543_Keypad, &key);
    TEST_ASSERT_EQUAL(0, keyStatus);
}

/* @brief check if a particular key is pressed */
void test_if_4_key_is_pressed(void)
{
    char key = '4';
    uint8_t keyStatus = 0;
    simular_tecla_presionada(key);
    keyStatus = keypad_check_status_key(&HC_543_Keypad, &key);
    TEST_ASSERT_EQUAL(1, keyStatus);
}