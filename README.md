# Introduction to Robotics (2021 - 2022)
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
