<div align="center">

# 🔧 TensPilot+ Hardware Device

**Arduino Uno-based Transcutaneous Electrical Nerve Stimulation (TENS) device for physical therapy and pain management.**

[![Hardware](https://img.shields.io/badge/Hardware-Arduino_Uno-00979D?logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Language](https://img.shields.io/badge/Language-C++-00599C?logo=c%2B%2B&logoColor=white)]()
[![License: All Rights Reserved](https://img.shields.io/badge/License-All%20Rights%20Reserved-red.svg)]()

</div>

---

## 📖 About the Project

The **TensPilot+ Hardware Device** is the physical component of the broader TensPilot+ ecosystem. It is a standalone, box-enclosed TENS unit designed to deliver targeted electrical impulses to nerve endings, helping to alleviate pain and support physical rehabilitation.

While the patient and provider software applications handle the tracking, analytics, and communication, this hardware device is solely responsible for generating and delivering the therapeutic electrical pulses safely.

---

## ✨ Features & Capabilities

- **Microcontroller:** Powered by an Arduino Uno for reliable pulse generation and timing.
- **4 Distinct Therapy Modes:** Programmed to deliver different wave patterns and frequencies (e.g., continuous, burst, modulated) tailored for various types of pain relief.
- **Standalone Operation:** Does not require Bluetooth or WiFi connectivity to function, ensuring 100% reliability during therapy sessions.
- **Safe Enclosure:** Housed in a custom-designed box unit for patient safety and portability.
- **Adjustable Intensity:** Allows the patient to manually dial in the exact stimulation strength required.

---

## 🏗️ How It Works (At a Glance)

1. The Arduino Uno runs a C++ program that generates precise square-wave PWM (Pulse Width Modulation) signals.
2. These signals are passed through a boosting circuit (transformer/transistor setup) to step up the voltage to a safe, therapeutic level.
3. The patient selects one of the 4 therapy modes via physical interface buttons.
4. The patient attaches the electrode pads to their skin, and the device delivers the electrical impulses.
5. After the session, the patient logs their usage and pain relief levels manually into the **TensPilot+ Patient App**.

*For a detailed breakdown of the circuit design and pulse generation logic, see [ARCHITECTURE.md](./ARCHITECTURE.md).*

---

## 📄 License

© Akachi240. All Rights Reserved. This hardware design, schematics, and embedded source code are not open source. No part of this repository may be copied, modified, or distributed without explicit permission from the author.

---

## 🔗 Related Software

- 📱 **[TensPilot+ Patient App](https://github.com/Akachi240/remix-of-tenspilot1)** — Companion app for patients to log sessions and track pain.
- 🩺 **[TensPilot+ Provider Dashboard](https://github.com/Akachi240/tenspilot-doctors-dashboard)** — Companion dashboard for doctors to monitor patient progress.
