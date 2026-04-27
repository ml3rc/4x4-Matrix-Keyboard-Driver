/*
 * matrix_keyboard.c
 * Created: 4/27/2026
 * Author: maell
 */

/* Include Files */
#include <avr/io.h>
#include <util/delay.h>
#include "matrix_keyboard.h"

/* Constants */
const char KEYS[4][4] = {
    {'1', '2', '3', '+'},
    {'4', '5', '6', '-'},
    {'7', '8', '9', '*'},
    {'C', '0', '=', '/'}
};

const uint8_t NCOLS = 4;
const uint8_t NROWS = 4;

/* Variables */
static char lastKey = '\0';
static char currentKey = '\0';




void KB_Init(void) {
    DDRK = 0x0F;  // Pins 0-3 output, 4-7 input
    PORTK = 0xFF; // Pull-ups on inputs, outputs high
    KB_UpdateKeyboard(); // Clear any initial key states
}

char KB_UpdateKeyboard(void) {
    currentKey = '\0'; // Default to no key pressed
    
    for (int col = 0; col < NCOLS; col++) {
        PORTK &= ~(1 << col); // Set column to 0
        _delay_us(1); // Delay for signal propagation
        for (int row = 0; row < NROWS; row++) {
            if ((PINK & (1 << (4 + row))) == 0) {
                PORTK |= (1 << col); // Set column back to 1
                currentKey = KEYS[row][col];
            }
        }
        PORTK |= (1 << col); // Set column back to 1
    }

    // Return the current key if it has changed since the last update
    if (currentKey != lastKey) {
        lastKey = currentKey;
        return currentKey;
    } else {
        return '\0'; // No change in key state
    }
}