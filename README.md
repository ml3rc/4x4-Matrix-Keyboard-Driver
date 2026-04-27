# 4x4 Matrix Keyboard Driver

A simple C library for interfacing with a 4x4 matrix keyboard on AVR microcontrollers.

## Description

This project provides a driver for a 4x4 matrix keyboard, commonly used in embedded systems for user input. The keyboard consists of 16 keys arranged in a 4x4 grid, connected through 8 pins (4 rows and 4 columns). This driver is specifically designed for Atmel ATmega2560 and similar AVR microcontrollers.

## How It Works

### Principles of Matrix Keyboards

A matrix keyboard reduces the number of pins required by arranging keys in a grid of rows and columns. Instead of using one pin per key (which would require 16 pins for 16 keys), it uses 8 pins total:

- **4 Row pins**: Connected to the rows of keys, configured as inputs with pull-up resistors.
- **4 Column pins**: Connected to the columns of keys, configured as outputs.

To detect key presses, the driver uses a scanning technique:

1. **Column Scanning**: The driver sets one column pin low at a time while keeping the others high.
2. **Row Reading**: For each column, it checks all row pins. If a row pin reads low, it means the key at the intersection of that row and column is pressed.
3. **Debouncing**: The code includes basic debouncing by only reporting key changes, preventing multiple detections of the same press. It is recommended to use in a fsm loop with 1-10ms loop delay.

### Key Layout

The keyboard layout is predefined as follows:

```
Row 0: 1  2  3  +
Row 1: 4  5  6  -
Row 2: 7  8  9  *
Row 3: C  0  =  /
```

### Hardware Connections

- Connect the 4 row pins to PORTK pins 4-7 (PK4-PK7) on the AVR microcontroller.
- Connect the 4 column pins to PORTK pins 0-3 (PK0-PK3) on the AVR microcontroller.
- Ensure pull-up resistors are enabled on the row pins.

## Usage

### Setup

1. Include the header file in your project:
   ```c
   #include "matrix_keyboard.h"
   ```

2. Call the initialization function once at startup:
   ```c
   KB_Init();
   ```

### Reading Keys

In your main loop or interrupt handler, call `KB_UpdateKeyboard()` to check for key presses:

```c
char key = KB_UpdateKeyboard();
if (key != '\0') {
    // A key was pressed or released
    // Handle the key press here
    switch (key) {
        case '1':
            // Handle '1' key
            break;
        case '+':
            // Handle '+' key
            break;
        // Add cases for other keys...
    }
}
```

**Note**: This driver is designed to be used in a Finite State Machine (FSM) loop with a loop delay of 1-10ms to ensure proper key detection and debouncing. Avoid calling it too frequently or without delays, as it may lead to unreliable key presses.

The function returns:
- The character of the pressed key if a new key is detected.
- `'\0'` if no key is pressed or if the same key is still held.

### Example Code

```c
#include <avr/io.h>
#include <util/delay.h>
#include "matrix_keyboard.h"

int main(void) {
    KB_Init();
    
    while (1) {
        char key = KB_UpdateKeyboard();
        if (key != '\0') {
            // Process the key
            // For example, send to UART or LCD
        }
        _delay_ms(5); // Loop delay for effective debouncing (1-10ms recommended)
    }
    
    return 0;
}
```

## API Reference

### Functions

- `void KB_Init(void)`: Initializes the keyboard pins and clears initial states.
- `char KB_UpdateKeyboard(void)`: Scans the keyboard and returns the current key press. Returns `'\0'` if no change.

### Constants

- `KEYS[4][4]`: 2D array defining the key layout.
- `NCOLS`: Number of columns (4).
- `NROWS`: Number of rows (4).

## Requirements

- AVR microcontroller (tested with ATmega series).
- AVR-GCC compiler.
- Standard AVR libraries (`avr/io.h`, `util/delay.h`).

## Limitations

- Basic debouncing: Only reports key changes, but may not handle very fast presses/releases perfectly.
- No support for multiple simultaneous key presses.
- Assumes specific pin assignments (PORTK).

## License

This project is open-source. Feel free to use and modify as needed.