# -PROJECT-digital_dimmer

electrical power control system on a resistive load by microcontroller p32MX250F128B controlled phase cut.

The system must have a microcontroller, a 4X4 keyboard, a 2X16 LCD screen and the additional hardware required for the application. 
The first line of the LCD screen should display the message “Dimmer” and in the second line the lighting percentage of the bulb should 
appear in the first 3 positions and in the following positions a set of staggered bars should appear that also represent said percentage. 
lighting percentage. Using the 4X4 keyboard, it should be possible to change the light intensity of the bulb in two ways. The first is to enter 
a value between 0 and 100 on the keyboard and then press the A key to set it. The second way is using the A and B keys, when you press the A key, 
the percentage must be increased by 1%, if you press B, the percentage must be decreased by 1%. Figure 1 shows a schematic of what should be 
displayed on the LCD screen. If a value outside the range is entered by keyboard or an incorrect key is pressed, a message should be displayed 
on the screen indicating "Invalid Action", and the system must keep running without changes, until a valid command is entered again.
