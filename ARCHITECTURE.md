# 🏗️ Hardware Architecture: TensPilot+

This document outlines the high-level system design and electronic architecture of the TensPilot+ hardware device.

---

## 🧠 System Overview

The TensPilot+ hardware is a standalone Transcutaneous Electrical Nerve Stimulation (TENS) unit. At its core, it uses an **Arduino Uno** to generate specific Pulse Width Modulated (PWM) waveforms. These waveforms are then amplified to therapeutic voltage levels before being delivered to the patient via electrode pads.

## 🔌 Hardware Components

### 1. Microcontroller (Arduino Uno)
- Acts as the brain of the device.
- Runs the embedded C++ firmware.
- Reads user inputs (mode selection, intensity adjustment).
- Generates precise timing signals for the electrical pulses.

### 2. Power Supply & Amplification
- **Power Source:** Battery operated (typically 9V) to ensure complete electrical isolation from mains power (a critical safety requirement for medical devices).
- **Boost Circuit:** TENS therapy requires higher voltages (often 30V-80V) but at extremely low, safe amperages (usually under 50mA). The Arduino's 5V PWM signal drives a switching transistor connected to a step-up transformer to achieve this therapeutic voltage.

### 3. User Interface (Physical)
- **Mode Selector:** Push-buttons or a rotary switch allowing the patient to toggle between the 4 programmed therapy modes.
- **Intensity Dial:** A potentiometer that scales the amplitude of the output pulses, allowing the patient to control the strength of the stimulation.
- **Status LEDs:** Indicators for power on, battery low, and active pulse delivery.

## 🌊 Therapy Modes (Firmware Logic)

The Arduino firmware dictates the shape, frequency, and duration of the electrical pulses. The device features 4 distinct modes, typically defined as:

1. **Continuous Mode:** Delivers a steady, uninterrupted train of pulses (typically around 80-100 Hz). Best for acute pain.
2. **Burst Mode:** Delivers short bursts of high-frequency pulses at a low background rate (e.g., 2 bursts per second). Designed to stimulate endorphin release for chronic pain.
3. **Modulated Mode:** Automatically varies the pulse width and frequency continuously. This prevents the nervous system from accommodating (getting used to) the signal.
4. **Mixed / Massage Mode:** A custom pattern alternating between high and low frequencies to simulate a tapping or massaging sensation.

## 🛡️ Safety Considerations

- **Optical Isolation / Transformer Coupling:** Ensures there is no direct DC path from the battery/microcontroller to the patient's skin.
- **Current Limiting:** Hardware resistors ensure the maximum delivered current never exceeds safe thresholds, regardless of firmware errors.
- **Standalone Nature:** By not relying on an app or wireless connection for active operation, the device avoids risks associated with connectivity drops, software lag, or smartphone battery failure during active electrical stimulation.
