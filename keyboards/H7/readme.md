# h7 keymap

keyboard layout editor [render](http://www.keyboard-layout-editor.com/#/gists/daf4d5f4f80466c4d7e5fa04a9b2b0b3)

## Setting unicode input mode

qmk input mode (information)[]:

Pressing the [Mode] key will cycle through the available unicode input modes.

The default mode is set to UC_LNX (Linux). This means that you would have to press mode once to apply UC_BSD.

Input Mode order:

1. UC_OSX
2. UC_LNX
3. UC_WIN
4. UC_BSD
5. UC_WINC
6. UC_OSX_RALT

Once the mode has been set, you should be able to write the expected unicode symbols to the screen.

The currently active mode can be persisted to the EEPROM with [Function]-[Mode], meaning that the option will be used reconnecting the keyboard.

If you do not persist the currently active unicode input mode to EEPROM, the previously set mode will be active the next time that you initialise (attach) the keyboard.

## Contributors

1. Jae-3soteric - The runner of the GB for this incredible board
2. Yiancar - PCB design and manu
3. Ellie - the boss
4. bit-shifter - keymap firmware
