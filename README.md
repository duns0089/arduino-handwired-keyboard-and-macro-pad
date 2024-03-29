# Arduino Firmware for Handwired 60% Keyboard
Two firmwares for an Arduino Pro-Micro used in a 60% keyboard. The keyboard switches are connected in a matrix with diodes are each switch. Each row and column is connected to a I/O pin on the Pro-Micro. The Arduino keyboard library is used to send key presses to the OS. 

# Single-Key (macro-pad functionality)
This code implementation heavily inspired by Datulab. This only provides functionality to click one key at a time, which is useful for a macro pad.

References:  
https://github.com/datulab/arduino-keyboard  
https://www.youtube.com/watch?v=Iq3oY91x9Vk  

# Multi-Key (keyboard functionality)
This implementation takes into consideration more keyboard functionality. The code builds on from the single key implementation. This includes:
* Multiple layers, such as a function layer for the F keys along the number line.
* Mod keys do not repeat. When a shift or CTRL key is pressed, it does not repeat it self like an alpha key would. This firmware recognised the mod keys and prevents them from repeating.
* Mod keys can be used in combination with other keys. When, say CTRL + W are clicked at the same time, both CTRL and W are registered at the same time allowing for multiple keys to be pressed. This functionality is good for shortcuts, a massive nice-to-have on a 60% keyboard.

# How to use this code
The reason I have left this implementation in is that I recommend starting with the single key implementation to understand how the I/O pins and the switch matrix really work. This also includes watching Datulab's video for a code explanation.  
  
Edit the constant variables to match your keyboard switch matrix. The important things to change are the inputs[] and outputs[], and keymaps. A Pro-Micro doesn't have to be used, the Arduino board just needs to have enough I/O pins for the rows and coloumns in the switch matrix. You can see in my keymap that I have to cut my rows in half to make less columns to fit the entire keyboard on the Pro-Micro.  