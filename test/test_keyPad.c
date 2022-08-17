/*
    El modulo a testear es el de manejo de un keypad 4x4
    Los test a ejecutar son los siguientes:
    -Key presionada
    -Estado de una key
    -Cambio de estado de una key
    -Testeo de secuencia de keys
    -Testeo de evento en base a secuencia de keys
*/

#include "unity.h"
#include "keypad.h"

/*Simulaciones*/
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
    keypad_4x4.flag1, keypad_4x4.flag2, keypad_4x4.flag3, keypad_4x4.flag4, keypad_4x4.flag5, keypad_4x4.flag6, keypad_4x4.flag7, 
    keypad_4x4.flag8, keypad_4x4.flag9, keypad_4x4.flag0, keypad_4x4.flagA, keypad_4x4.flagB,
    keypad_4x4.flagC, keypad_4x4.flagD, keypad_4x4.flagAst, keypad_4x4.flagHash = 0;
}

/*Tests*/

keypadPinout HC_543_Keypad;

void setUp(void)
{
    simulated_no_key_pressed();
    keypad_init(&HC_543_Keypad);
}

/* @brief check if a specific key is pressed */
void test_pressed_key_is_A(void)
{
    char key = 'A';
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