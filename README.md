# Introduction to Robotics (2022 - 2023)
Introduction to robotics optional course from the Faculty of Mathematics and Computer Science, University of Bucharest.

Each homework will be presented listing requirements, implementation details, code and image files.

# Homework 1

**Schema:**

![asd](/Homework/H1/H1-schema.jpg)

**Photo of setup:**

![asd](/Homework/H1/H1-pic.jpg)

**[Demo video](https://youtu.be/bqaiuz9O_BU)**

**Components:**

1. RBG led (1 minimum)
2. potentiometers (3 minimum)
3. resistors and wires (per logic)

**Technical Task:**

Use a separat potentiometer in controlling each of thecolor of the RGB led (Red,Green and Blue). The control must be done with digital electronics(aka you must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connected to the led.

**Publishing task:**

You must add the code to the Github repo and continue updating the README with at least the following details (but feel free to be more creative):

1. Task Requirements
2. Picture of the setup
3. Link to video showcasing functionality (I recommend youtube, butanything I can access is fine)
4. Remember to publish the video in the correct orientation. 👎 Don’t do this: https://youtu.be/Y8H0PlUtcto5. Hand in the homework on MS teams when done - aka when github is up to date

**Coding task:**

1. Coding style is of utmost importance.<br>
2. You must have a perfectly clean code in order to receive the maximum grade.<br>
3. Keep in mindthat magic numbers are not accepted, although you might see them in the lab (as a trade-off for speed). Remember to be consistent in your style, check the style guide and the provided style document and use correct spacing.<br>


# Homework 2

**Schema:**

![asd](/Homework/H2/H2-schema.jpg)

**Photo of setup:**

![asd](/Homework/H2/H2-pic.jpg)

**[Demo Video](https://youtu.be/KTbNv_8KV-Y)**<br>

**Components:**<br>
- 5 LEDs
- 1 button
- 1 buzzer
- resistors and wires (per logic)

**Technical Task:**<br>
Building the traffic lights for a crosswalk. You will use 2 LEDs to represent the traffic lights for people (red and green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green). The system has the following states:

- State 1 (default, reinstated after state 4 ends): green light for cars, red light for people, no sounds. Duration: indefinite, changed by pressing the button.
- State 2 (initiated by counting down 8 seconds after a button press): the light should be yellow for cars, red for people and no sounds. Duration: 3 seconds.
- State 3 (initiated after state 2 ends): red for cars, green for people and a beeping sound from the buzzer at a constant interval. Duration: 8 seconds.
- State 4 (initiated after state 3 ends): red for cars, blinking green for people and a beeping sound from the buzzer, at a constant interval, faster than the beeping in state 3. Duration: 4 seconds.


# Homework 3

**Photo of setup:**

![asd](/Homework/H3/H3-pic.jpg)

**[Demo Video](https://youtu.be/0WtFF89WT5M)**<br>

**Components:**<br>
- 1 7-segment display
- 1 joystick
- resistors and wires (per logic)

**Technical Task:**<br>
Use the joystick to control the position of the segment and ”draw” on the display. The movement between segments should be natural (meaning they should jump from the current position only to neighbors, but without passing through ”walls”. The system has the following states:

- State 1 (default, but also initiated after a button press in State 2): Current position blinking. Can use the joystick to move from one position to neighbors. Short pressing the button toggles state 2. Long pressing the button in state 1 resets the entire display by turning all the segments OFF and moving the current position to the decimal point
- State 2 (initiated after a button press in State 1): The current segment stops blinking, adopting the state of the segment before selection (ON or OFF). Toggling the Y axis should change the segment state from ON to OFF or from OFF to ON. Clicking the joystick should save the segment state and exit back to state 1


# Homework 4

**Photo of setup:**

![asd](/Homework/H4/H4-pic.jpg)

**[Demo Video](https://youtu.be/QKMn-xxjLUM)**<br>

**Components:**<br>
- 1 4 digit 7-segment display
- 1 74hc595 shiftregister
- 1 joystick
- resistors and wires (per logic)

**Technical Task:**<br>
Use the joystick to move through the 4 digit 7 segment displays digits, press the button to lock in on the current digit and use the other axis to increment or decrement the number. Keep the button pressed to reset all the digit values and the current position to the first digit in the first state. The system has the following states:

- State 1: the joystick axis can be used to cycle through the 4 digits; using the other axis does nothing. A blinking decimal point shows the current digit position. When pressing the button, the selected digit is locked in and the system goes to the second state.

- State 2: in this state, the decimal point stays always on, no longer blinking and the axis can no longer be used to cycle through the 4 digits. Instead, using the other axis, the number on the current digit can be incremented or decremented IN HEX (aka from 0 to F). Pressing the button again returns to the previous state.

- Reset: toggled by long pressing the buttononly in the first state. When resetting, all the digits go back to 0 and the current positionis set to the first (rightmost) digit, in the first state.

# Homework 5

**Photo of setup:**

![asd](/Homework/H5/H5-pic.jpg)

**[Demo Video of the menu](https://youtu.be/NSpRQAL45rI)**<br>

**[Demo Video of the first level](https://youtu.be/zvDQvhPP4PI)**<br>

**Components:**<br>
- 1 LCD display
- 1 8x8 LED matrix
- 1 74hc595 shiftregister
- 1 joystick
- 1 potentiometer
- resistors and wires (per logic)

**[Technical Task](https://github.com/TudorCosmin/IntroductionToRobotics/blob/main/Homework/H5/Matrix%20project%20requirements.pdf)**<br>
