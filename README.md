Interfacing 16x2 LCD display with STM32F1xx Microcontroller
________________________________________
________________________________________

Objective:
•	Learn GPIO configuration in STM32F103C8T6 using CMSIS registers.
•	Understand structs and pointers in C for hardware abstraction.
•	Interface a 16x2 LCD in 4-bit mode
•	Learn proper folder organization for STM32 projects.
________________________________________
________________________________________
Hardware Required
________________________________________
________________________________________
Component	Quantity	Notes
STM32F103C8T6 (Bluepill)	1	
ST-Link / USB Programmer	1	To flash code
16x2 LCD (HD44780)	1	Standard LCD
Jumper wires	—	Male-Male
10kΩ Potentiometer	1	For contrast
Breadboard	1	Optional
________________________________________
________________________________________
LCD Pin Connections:
________________________________________
________________________________________
LCD Pin	STM32 Pin	Notes
RS	PA0	Register Select
EN	PA1	Enable
D4	PA2	Data bit 4
D5	PA3	Data bit 5
D6	PA4	Data bit 6
D7	PA5	Data bit 7
RW	GND	Write-only mode
VSS	GND	Ground
VDD	+5V	Supply
VEE	Pot 10k	Contrast adjustment
________________________________________
________________________________________

STM32 Project Folder Structure
________________________________________
________________________________________
When creating a project in STM32CubeIDE (or any CMSIS/GCC project), organize files like this:
CMSIS_LCD_Project/
│
├── Core/
│   ├── Src/
│   │   ├── main.c       <-- Your main program
│   │   └── lcd.c        <-- LCD driver implementation
│   └── Inc/
│       └── lcd.h        <-- LCD driver header file
│
├── Drivers/             <-- Optional for future drivers
└── Makefile / project settings
Key Points:
1.	Put lcd.h in Core/Inc/
2.	Put lcd.c in Core/Src/
3.	Include header in main.c like:
#include "lcd.h"
STM32CubeIDE will automatically include Core/Inc/ in include path. If using Makefile, ensure -ICore/Inc is added.
________________________________________
________________________________________
 Build & Flash Instructions
________________________________________
________________________________________
1.	Open STM32CubeIDE, create a GCC Empty Project, select STM32F103C8.
2.	Copy lcd.h → Core/Inc, lcd.c → Core/Src, main.c → Core/Src.
3.	Build the project. Fix include paths if needed (-ICore/Inc).
4.	Connect ST-Link, flash using Debug → ST-Link.
5.	LCD should display “Hello STM32! LiquidCrystal”.
________________________________________
