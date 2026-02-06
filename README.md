# 🎛️ TR-DZ : Tech House Groovebox

![Status](https://img.shields.io/badge/Status-Prototype-yellow)
![Platform](https://img.shields.io/badge/Platform-Daisy%20Seed-blue)
![Audio](https://img.shields.io/badge/Audio-48kHz%20%2F%2024bit-green)

**The TR-DZ is a custom-built, DSP-powered drum machine designed specifically for the heavy low-end requirements of Tech House and Techno production.**

Currently in **Prototype Phase (V1)**. Powered by the [Electro-Smith Daisy Seed](https://www.electro-smith.com/daisy).

---

## 🚀 Audio Architecture (V26 Engine)

Unlike standard drum machines that mix everything into a single bus, the TR-DZ uses a **Dual-Bus Studio Architecture** to ensure the Kick and Bass can be saturated heavily without destroying the clarity of the High Hats.

### 🔊 1. Low-End Bus (The "Dirty" Channel)
Dedicated to the Kick and Bass. This bus passes through a custom `DirtyClip` saturation stage (`tanh` based) to glue the rhythm section together.
* **Kick "Hammer" Engine:** Uses a **Cubic Pitch Envelope** (`env^3`) instead of standard linear decay. This creates a massive transient impact (800Hz to 40Hz in milliseconds).
* **Bass "Titanium" Engine:** **PolyBLEP Square Wave** with pre-filter saturation and a resonant Low-Pass Filter. Designed for sub-bass "rumble".

### 💎 2. High-End Bus (The "Clean" Channel)
Dedicated to Hats and Claps. This bus bypasses the heavy distortion.
* **Crisp Hats:** White noise shaped by a high-resonance **High-Pass Filter**.
* **Natural Clap:** Band-pass filtered noise focused on 1kHz for an organic, woody snap.

---

## 🛠️ Hardware Specs (V1 Prototype)

* **MCU / DSP:** Daisy Seed (STM32 H7)
* **Multiplexer:** CD74HC4067 (16-Channel Analog Mux)
* **Controls:** 9 Analog Potentiometers mapped to real-time DSP parameters:
    * Tune, Decay, Click (Kick)
    * Sidechain Compression (Bass)
    * Drive / Saturation (Master)
    * Tech Factor (Macro Filter Control)
* **Output:** Stereo Line Out

---

## 🗺️ Roadmap

- [x] **DSP Engine V26 (Stable)** - *Completed*
- [x] **Breadboard Prototype** - *Completed*
- [ ] **PCB Design (EasyEDA)** - *In Progress*
- [ ] **Aluminum Enclosure Design**
- [ ] **V2 Firmware:** Adding MIDI In/Out support

---

## 💻 Building the Firmware

This project is built using the `libDaisy` and `DaisySP` libraries.

1.  Clone the repo:
    ```bash
    git clone [https://github.com/ZifouAudio/TR-DZ.git](https://github.com/ZifouAudio/TR-DZ.git)
    ```
2.  Navigate to the directory and build:
    ```bash
    cd Firmware
    make
    ```
3.  Flash to Daisy Seed:
    ```bash
    make program-dfu
    ```

---

### 📬 Contact & Socials

**Developed by Zifou Audio**
Follow the development journey on Instagram: [@zifouaudio](https://www.instagram.com/zifouaudio)
