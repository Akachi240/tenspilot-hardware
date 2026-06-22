# 🏗️ Hardware Architecture: TensPilot+

This document outlines the high-level system design and electronic architecture of the TensPilot+ hardware device.

---

## 🧠 System Overview

The TensPilot+ hardware is a standalone Transcutaneous Electrical Nerve Stimulation (TENS) unit. At its core, it uses an **Arduino Uno** to generate specific Pulse Width Modulated (PWM) waveforms. These waveforms are amplified to therapeutic voltage levels before being delivered to the patient via electrode pads.

## 🔌 Hardware Components

### 1. Power Supply & Amplification
- **Power Source:** Flat lithium-ion batteries (similar to those found in phones or power banks), connected to a 5V output panel.
- **Power Distribution:** The 5V output splits into two paths:
  1. Powers the Arduino Uno (controlled via a main power switch).
  2. Connects to a **Boost Converter** that amplifies the voltage.
- **Output Stage:** The amplified high voltage from the boost converter is sent to an **L298N Motor Driver**, which is rapidly switched by the Arduino's PWM signals to generate the final TENS therapy pulses.

### 2. Microcontroller (Arduino Uno)
- Acts as the brain of the device.
- Runs the embedded C++ firmware.
- Reads user inputs from potentiometers and pushbuttons.
- Drives the LCD screen and indicator LEDs.
- Outputs precise timing signals to the L298N driver.

### 3. User Interface (Physical)
- **LCD Display:** A screen displaying real-time session stats (Mode, Pulse frequency, Level/Intensity percentage, and Active status).
- **Control Inputs:**
  - **1x Mode Pushbutton:** Cycles through the 4 programmed therapy modes.
  - **3x Potentiometers:** Allow the user to manually dial in the exact **Frequency**, **Intensity**, and **Pulse Width**.
- **Switches & Safety:**
  - **Main Power Switch:** Turns the device on/off.
  - **LED Switch:** Toggles the illumination.
  - **Emergency Stop Switch:** Instantly cuts power to the L298N driver for immediate safety.
- **Indicator Lights:**
  - **4x Mode LEDs:** Visually indicate which of the 4 therapy modes is currently active.
  - **1x Emergency Stop LED:** Illuminates when the emergency stop is engaged.
  - **Battery Percentage Display:** Shows the remaining battery charge.

## 🌊 Therapy Modes (Firmware Logic)

The Arduino firmware dictates the shape, frequency, and duration of the electrical pulses. The device features 4 distinct modes, cycled via the mode pushbutton:

1. **Continuous Mode:** Delivers a steady, uninterrupted train of pulses. Best for acute pain.
2. **Burst Mode:** Delivers short bursts of high-frequency pulses at a low background rate. Designed to stimulate endorphin release for chronic pain.
3. **Modulated Mode:** Automatically varies the pulse width and frequency continuously. This prevents the nervous system from accommodating to the signal.
4. **Mixed / Massage Mode:** A custom pattern alternating between high and low frequencies to simulate a tapping or massaging sensation.

## 🛡️ Safety Considerations

- **Emergency Stop:** A dedicated physical switch instantly disables the L298N driver, physically stopping all electrical output to the pads immediately.
- **Battery Operation:** Ensures complete electrical isolation from mains power, a critical safety requirement for medical devices.
