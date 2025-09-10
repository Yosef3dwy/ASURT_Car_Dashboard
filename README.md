# ASURT_Car_Dashboard


Formula Car Dashboard with Nextion Display and STM32
This repository contains the firmware and design files for a custom formula car dashboard. The system is built around an STM32F103C8T6 microcontroller and a Nextion HMI display, designed to provide critical real-time data to the driver.

Project Overview
The dashboard is a custom module that acts as a listening node on the vehicle's CAN bus. It is responsible for receiving and interpreting data broadcasted by other systems on the vehicle's network. The STM32 microcontroller processes these CAN messages and translates them into visual updates on a Nextion NX4827P043-011C display via the UART protocol, delivering essential information to the driver during a race.

The system is designed with an efficient event-driven architecture, meaning the display only updates when new, relevant data is received, optimizing performance.

Key Hardware
Microcontroller: STM32F103C8T6 ("Blue Pill")

HMI Display: Nextion NX4827P043-011C (4.3" Capacitive Touch)

System Architecture & Features
The dashboard interface is built around a single Racer Page. This screen serves as the driver's main information hub during a race, displaying key vehicle parameters in a clear and easy-to-read format.

Displayed Parameters:
📊 Electrical RPM (ERPM): Visualized as a dynamic slider/gauge.

🏎️ Vehicle Speed: Calculated in real-time from the two front wheel proximity sensors.

🌡️ Motor Temperature: Monitors motor health to prevent overheating.

🔋 Battery State: Displays the current state of charge or voltage.

🦶 Throttle Position: Represented by a slider indicating throttle input.

🛑 Brake Pressure: Represented by a slider indicating braking force.

⏱️ Lap Stopwatch: A fully functional stopwatch to track lap times.

Lap Stopwatch Functionality
The stopwatch is controlled directly by the driver using buttons on the steering wheel:

Start/Stop: Begin or end a lap timing session.

Pause/Unpause: Temporarily halt and resume the timer.

Best Lap: The system automatically records and displays the best lap time whenever the stopwatch is stopped.

CAN Bus Data Reception
The STM32 microcontroller is the central hub for processing data from the car's network.

Listening Node: The firmware configures the STM32 to act as a CAN node, continuously monitoring the bus for incoming data packets.

Message Filtering: It uses hardware or software filters to listen specifically for CAN IDs that correspond to the parameters displayed on the dashboard (e.g., ERPM, motor temp, etc.). This ensures that the microcontroller only processes relevant information, improving efficiency.

Data Parsing: Upon receiving a valid message, the STM32 extracts the data payload. It then parses this data to get the actual value for the parameter.

Display Update: Finally, the parsed value is formatted into a command string and sent to the Nextion display via UART to update the visual component (like a gauge or slider).

Data Update Logic
Speed Calculation (Proximity Sensors): Speed updates are uniquely event-driven.

Mechanism: Proximity sensors are mounted near the front wheel hubs. As a wheel rotates, triggers (like bolt heads or magnets) on the hub pass by the sensor, which generates a digital pulse for each pass.

Calculation: The STM32 microcontroller captures these pulses as interrupts. By measuring the time between consecutive pulses or counting pulses over a fixed time interval, it calculates the rotational speed (RPM) of each front wheel. This RPM value, combined with the known circumference of the tire, is used to calculate the linear speed of the vehicle.

CAN-based Parameters: The ERPM, Throttle Position, Brake Pressure, Motor Temperature, and Battery State are all updated in real-time upon receiving their respective CAN messages from other vehicle systems, as described in the section above.

Getting Started
To get this project running, you will need:

Hardware: The STM32F103C8T6 board and the Nextion display mentioned above.

Software:

An IDE for STM32 development (e.g., STM32CubeIDE, Keil, IAR).

The Nextion Editor to upload the HMI file to the display.

Firmware: Flash the firmware from this repository onto the STM32 microcontroller.

HMI File: Upload the .HMI file (found in the /Nextion directory) to the display using the Nextion Editor.

This project is developed for the 

YourTeamName/UniversityName
 Formula Student team.
