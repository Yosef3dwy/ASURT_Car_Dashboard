# Formula Car Dashboard with Nextion Display and STM32

This repository contains the firmware and design files for a custom Formula Student car dashboard.  
The system is built around an **STM32F103C8T6 (Blue Pill)** microcontroller and a **Nextion HMI display**, designed to provide critical real-time data to the driver.

---

## 📖 Project Overview
The dashboard is a custom module that acts as a **listening node** on the vehicle's CAN bus.  
It receives and interprets data broadcasted by other systems on the vehicle's network. The STM32 microcontroller processes these CAN messages and translates them into visual updates on a **Nextion NX4827P043-011C display** via the UART protocol, delivering essential information to the driver during a race.

The system is designed with an **efficient event-driven architecture**, meaning the display only updates when new, relevant data is received, optimizing performance.

---

## 🔧 Key Hardware
- **Microcontroller**: STM32F103C8T6 ("Blue Pill")  
- **HMI Display**: Nextion NX4827P043-011C (4.3" Capacitive Touch)

---

## ⚙️ System Architecture & Features
The dashboard interface is built around a **single Racer Page**, serving as the driver's main hub during a race.

### Displayed Parameters
- 📊 **Electrical RPM (ERPM):** Visualized as a dynamic slider/gauge.  
- 🏎️ **Vehicle Speed:** Calculated in real-time from the two front wheel proximity sensors.  
- 🌡️ **Motor Temperature:** Monitors motor health to prevent overheating.  
- 🔋 **Battery State:** Displays the current state of charge or voltage.  
- 🦶 **Throttle Position:** Represented by a slider indicating throttle input.  
- 🛑 **Brake Pressure:** Represented by a slider indicating braking force.  
- ⏱️ **Lap Stopwatch:** Fully functional stopwatch to track lap times.  

---

## ⏱️ Lap Stopwatch Functionality
The stopwatch is controlled directly by the driver using **steering wheel buttons**:

- **Start/Stop:** Begin or end a lap timing session.  
- **Pause/Unpause:** Temporarily halt and resume the timer.  
- **Best Lap:** Automatically records and displays the best lap time whenever the stopwatch is stopped.  

---

## 🚌 CAN Bus Data Reception
The STM32 microcontroller is the central hub for processing CAN data.

- **Listening Node:** Continuously monitors the CAN bus for incoming data packets.  
- **Message Filtering:** Hardware/software filters ensure only relevant CAN IDs (ERPM, motor temp, etc.) are processed.  
- **Data Parsing:** Extracts and interprets payload values from valid messages.  
- **Display Update:** Sends formatted command strings via UART to update the Nextion display components.  

---

## 📐 Data Update Logic
### Vehicle Speed (Proximity Sensors)
- **Mechanism:** Proximity sensors on front wheel hubs generate digital pulses as triggers (e.g., bolts/magnets) pass.  
- **Calculation:** STM32 measures the time between pulses or counts pulses per interval → calculates wheel RPM.  
- **Conversion:** Wheel RPM + tire circumference → vehicle speed (linear).  

### CAN-Based Parameters
- **ERPM, Throttle Position, Brake Pressure, Motor Temp, Battery State**  
  → Updated in real-time from CAN messages.  

---

## 🚀 Getting Started
To run this project, you will need:

### Hardware
- STM32F103C8T6 board  
- Nextion NX4827P043-011C display  

### Software
- **IDE for STM32 development:** STM32CubeIDE, Keil, or IAR  
- **Nextion Editor:** For uploading the HMI file to the display  

### Setup
1. Flash the firmware from this repository onto the STM32 microcontroller.  
2. Upload the `.HMI` file (found in `/Nextion`) to the display using the Nextion Editor.  

---

## 🏎️ Formula Student Team
This project is developed for the **YourTeamName / UniversityName** Formula Student team.
