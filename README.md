# Open-Remote POC
<div>
    <img src="https://i.imgur.com/nlkHP9E.jpg" height=283>
    <img src="https://i.imgur.com/Hb0BHG4.jpg" width=400>
</div>

## Table of content
1. [Description](#description)
2. [Project scope and constraints](#scope-&-constraints)
3. [Technologies](#technologies)
4. [Schematics & build guide](#schematics-&-build-guide)
5. [How it works](#how-it-works)
6. [TODO for POC](#todo-for-poc)
7. [TODO for final version](#todo-for-final-version)


## Description & Goals
Open-remote is a universal remote control operating at 38khz, built using a ESP-32 microcontroller. It is currently a proof-of-concept and needs additional features in order for it to replace a remote control (see [todo](#todo-for-final-version) for more information).

The prototype shown in pictures only uses a single assignable button due to space constraints in the breadboard, but it is easily configurable to use a button matrix as input, for a wider selection of controls to map. More information about configuring a button matrix on ```lib/src/keypad_interactor.cpp```.

The goals for this project was to learn more about embedded systems, low-level programming, and infrared modulation. I did **not** aim to create a commercially viable product in any way.

## Scope & Constraints
The scope of the POC was to build a remote controller that is able to:
- Receive 38khz encoded infrared data from any consumer remote operating at the same frequency.
- Decode it.
- Assign the data to a specific button.
- Transmit it back so that the device responds to the command.
- Show instructions on display.

What was **not** in-scope was the operational distance of the remote, which is currently 1m, and persistent storage. See the [todo](#todo) section for more details.

The constraints of the first iteration were:
- Has to be built on a single breadboard.
- Has to have one assignable button, but needs to support a button matrix.

## Technologies (revise)
- ESP-32 Microcontroller programmed in C++
- IRremote library for receiving IR data.
- Keypad library for handling button matrixes.

## Schematics & build guide
Material List:
- ESP32 development board 
- 2x button switches for single-button build **OR** 1x button switch + button matrix
- Infrared LED
- 220ohm resistor
- IR receiver (I used a TSOP4838)

[Schematic for prototype build with single assignable button](https://i.imgur.com/nlkHP9E.jpg)

[Image of breadboard prototype](https://i.imgur.com/Hb0BHG4.jpg)

## How it works
Open-remote has two modes: Pairing mode & Remote mode.

As the names suggest, pairing mode is used for detecting an IR signal and assigning the data to a specific button, while remote mode listens for button presses and emits the IR data that is assigned to the button. There are two buttons in the prototype: One for changing modes (pairing & remote), and one that acts as an assignable button.

When the remote is first turned on, it will begin pairing mode automatically, and to clone an IR signal, you will need to to point a remote control to the open-remote and press a key you would like to clone. Once the open-remote receives an IR signal you need to press an assignable button, and the IR data should be saved to it. Note that there is no persistent storage in the current version.

In order to change it to remote mode, you would have to press the uppermost button as shown in the schematic. Once in remote mode, you can press any buttons that have IR data assigned to them, and the IR LED will emit the signal that was saved. 

The mode-changing button can be pressed at any time and it will pause the state of whichever mode you were in as it changes. E.g. if the open-remote receives IR data in pairing mode, it will prompt you to press an assignable button, and if you change to remote mode before assigning, you can go back to pairing mode and continue the assignment of the IR data received without losing progress.

## Todo for POC
- Make instructions appear on display.

## Todo for final version
- Implement persistent storage.
- Learn more about transistors and how they can assist in increasing the operational distance of open-remote
- Make keypad_handler more generic so that a single button can be used instead of having to adapt the code.
