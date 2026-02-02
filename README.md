# 🥁 TR-DZ : Daisy Seed Tech House Drum Machine
[![Démo TR-DZ sur YouTube](https://img.youtube.com/vi/K2HNfEA7Zsw/0.jpg)](https://www.youtube.com/shorts/K2HNfEA7Zsw)
> 📹 **Clique sur l'image pour voir la démo (Son activé !)**

# 🎹 TR-DZ Ultimate: The Next-Gen Tech House Engine

![Version](https://img.shields.io/badge/Version-V11-blue)
![Platform](https://img.shields.io/badge/Hardware-Daisy_Seed-green)
![Status](https://img.shields.io/badge/Status-Prototype_Alpha-orange)

**TR-DZ** (Tech-House Rhythm - Dual Zone) is a hybrid rhythm synthesis station designed for live performance. Heavily inspired by the *TRK-01* workflow, it focuses on the visceral symbiosis between the Kick and the Bass through dedicated hardware and software architecture.

> **Philosophy:** Zero Friction. One knob = One function. Ears over eyes.

---

## ✨ Key Features

- **Native Sidechain (Native Ducking):** A proprietary DSP algorithm where the Kick dynamically drives the Bass amplitude for a perfect mix without external compression.
- **Hybrid Synthesis:** Fusion of modeled synthesis (Sin/Square/Saw oscillators) and high-fidelity sample playback.
- **Generative AI:** Integrated "Assisted Sound Design" models for instant pattern generation and sonic mutation.
- **Powerful Hardware:** Based on the **Daisy Seed (STM32H7)** microcontroller, delivering 24-bit / 48kHz audio resolution.

---

## 🛠 Technical Specifications

### Software Architecture
- **DSP Core:** Written in C++ (libdaisy / daisysp).
- **V11 Engine:** Implemented interactive mixing engine (Ducking Logic).
- **Multiplexing:** Management of 16 analog inputs via a single ADC pin using the CD74HC4067.



### Hardware Architecture (Target)
- **CPU:** Dual Daisy Seed (Master/Slave distributed architecture).
- **Interface:** 36 potentiometers, 12 faders, Nextion screen for dedicated graphical UI.
- **Storage:** SD card support for sample libraries.

---

## 🚀 Getting Started

### Prerequisites
- [DaisyToolchain](https://github.com/electro-smith/DaisyToolchain) installed.
- A **Daisy Seed** controller.
- A **CD74HC4067** multiplexer (for full potentiometer support).

### Build & Flash
1. Clone the repository:
   ```bash
   git clone [https://github.com/Zifou-maker/TR-DZ-Ultimate.git](https://github.com/Zifou-maker/TR-DZ-Ultimate.git)
