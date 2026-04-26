⏱️ Digital Clock with Stopwatch using 8051
## Basic Information
This project is a microcontroller-based application that implements a Digital Clock and Stopwatch system using the 8051 (AT89C51) microcontroller. It is designed to display time and measure elapsed time using an LCD interface and user input controls.


## Functions
- Displays current time in HH:MM:SS format
- Stopwatch functionality
- Start, Stop, and Reset operations
- Mode switching between clock and stopwatch
- Continuous time update using timer interrupts


 ## User Interface
 # Display (LCD Interface)
- A **16x2 LCD display** is used as the primary output device.
- The display shows:
  - Clock Mode: Current time in HH:MM:SS format
  - Stopwatch Mode:Elapsed time in HH:MM:SS format
- The first row typically displays the mode (Clock / Stopwatch).
- The second row displays the running time.
- The display updates continuously in real time.

# User Controls (Push Buttons)
Push buttons are provided for user interaction:
- Mode Button:
  - Switches between Clock Mode and Stopwatch Mode
- Start Button:
  - Starts the stopwatch counting
- Stop Button:
  - Pauses the stopwatch
- Reset Button:
  - Resets stopwatch time to 00:00:00
# Interaction Flow
- On power-up, the system starts in Clock Mode
- User can switch to Stopwatch Mode using the mode button
- In stopwatch mode:
  - Start → begins counting
  - Stop → pauses time
  - Reset → clears time
  # Hardware Components
- AT89C51 Microcontroller
- 16x2 LCD Display
- Push Buttons
- Crystal Oscillator (11.0592 MHz)
- Resistors and Capacitors
- Power Supply


 # Software Used
- Keil uVision (Embedded C programming)
- Proteus Design Suite (Simulation)


## Working Principle
#Time Generation:
The system uses the internal timers of the 8051 microcontroller to keep track of time. A crystal oscillator provides clock pulses, which help in generating accurate one-second delays. By counting these delays, the system updates seconds, minutes, and hours.

#Clock Mode:
When the system is powered on, it starts in Clock Mode. The time is continuously updated and displayed on the LCD in HH:MM:SS format. Every second, the display refreshes automatically to show the current time.

#Stopwatch Mode:
When the user presses the mode button, the system switches to Stopwatch Mode. In this mode, time starts from 00:00:00.
Start button begins counting
Stop button pauses the time
Reset button clears the time

#User Input:
Push buttons are connected to the microcontroller to control the system. The controller continuously checks for button presses and performs actions like switching modes or controlling the stopwatch.

#Display Operation:
A 16x2 LCD is used to display the output. It shows the current mode and the time. The display updates continuously so the user can see real-time changes clearly.

Overall Operation:
The system runs continuously in a loop where it updates time, checks user input, and refreshes the display. This ensures smooth and accurate operation of both the clock and stopwatch.


 ## Circuit Design
The circuit consists of:
- 8051 microcontroller as the main control unit
- LCD connected for output display
- Push buttons connected to input pins
- Crystal oscillator for clock generation
- 






