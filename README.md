<div align="center">

# 🔧 TensPilot+ Hardware Device

**Arduino Uno-based Transcutaneous Electrical Nerve Stimulation (TENS) device for physical therapy and pain management.**

[![Hardware](https://img.shields.io/badge/Hardware-Arduino_Uno-00979D?logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Language](https://img.shields.io/badge/Language-C++-00599C?logo=c%2B%2B&logoColor=white)]()
[![License: All Rights Reserved](https://img.shields.io/badge/License-All%20Rights%20Reserved-red.svg)]()

</div>

---

## 📖 About the Project

The **TensPilot+ Hardware Device** is the physical component of the broader TensPilot+ ecosystem. It is a standalone, custom-built TENS unit designed to deliver targeted electrical impulses to nerve endings, helping to alleviate pain and support physical rehabilitation.

While the patient and provider software applications handle the tracking, analytics, and communication, this hardware device is solely responsible for generating and delivering the therapeutic electrical pulses safely.

---

## ✨ Features & Capabilities

- **Microcontroller:** Powered by an Arduino Uno for reliable pulse generation and timing.
- **Amplification System:** Utilizes a 5V lithium-ion battery setup feeding into a boost converter and an L298N driver to deliver safe, therapeutic voltages.
- **4 Distinct Therapy Modes:** Programmed to deliver different wave patterns and frequencies (e.g., continuous, burst, modulated) tailored for various types of pain relief.
- **Physical UI & LCD:** Features an LCD screen for real-time stats, 3 potentiometers (Frequency, Intensity, Pulse Width), and mode indicator LEDs.
- **Hardware Safety:** Includes an Emergency Stop switch that instantly kills power to the driver module.
- **Standalone Operation:** Does not require Bluetooth or WiFi connectivity to function, ensuring 100% reliability during therapy sessions.

---

## 🏗️ How It Works (At a Glance)

1. **Power Routing:** Flat lithium batteries output 5V. This 5V powers the Arduino and also feeds a boost converter.
2. **Amplification:** The boost converter steps up the voltage and sends it to an L298N motor driver.
3. **Pulse Generation:** The Arduino generates precise square-wave PWM signals based on the user's potentiometer settings (frequency, pulse width, intensity).
4. **Delivery:** The Arduino switches the L298N driver to deliver the amplified pulses to the patient's electrode pads.
5. **Tracking:** After the session, the patient logs their usage and pain relief levels manually into the **TensPilot+ Patient App**.

*For a detailed breakdown of the circuit design and components, see [ARCHITECTURE.md](./ARCHITECTURE.md).*

---

## 📄 License

© Akachi240. All Rights Reserved. This hardware design, schematics, and embedded source code are not open source. No part of this repository may be copied, modified, or distributed without explicit permission from the author.

---

## 🔗 Related Software

- 📱 **[TensPilot+ Patient App](https://github.com/Akachi240/remix-of-tenspilot1)** — Companion app for patients to log sessions and track pain.
- 🩺 **[TensPilot+ Provider Dashboard](https://github.com/Akachi240/tenspilot-doctors-dashboard)** — Companion dashboard for doctors to monitor patient progress.
