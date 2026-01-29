# TR-DZ: The Ultimate Tech House Kick Synthesizer

**Powered by Daisy Seed (Electro-Smith)**

TR-DZ is a performance instrument dedicated to creating punchy and organic Tech House kicks. Built on the Daisy Seed platform, it combines modeled analog synthesis (DSP) with an advanced control interface via multiplexing.

## ✨ Key Features

* **Dual-Envelope Engine:** Independent management of the amplitude envelope (the body) and the pitch envelope (the "punch").

* **Analog-Style Saturation:** Non-linear saturation algorithm based on the arctangent function ($\arctan$) for authentic harmonic warmth.

* **Ghost Mode:** Organic variation algorithm introducing subtle micro-differences on each hit to avoid monotony.

 * **16-Parameter Interface:** Full control of the kick drum's DNA via the CD4051 multiplexer.

* **OLED UI:** Real-time visual feedback on the SH1106 screen.

## 🛠️ Technical Specifications

### Hardware
* **Core:** Daisy Seed (STM32H7) - 480MHz / 24-bit audio.

* **Multiplexing:** CD4051 (Expansion via 8 to 16 potentiometers).

 * **Display:** 1.3" OLED I2C (SH1106).
* **Power Supply:** Rail filtered via AGND for complete radio silence.

### Signal Flow (DSP)
* **Oscillator:** Sliding frequency Triangle/Sine waveform.
* **Impact:** Ultra-fast Pitch Envelope (50ms) for transient snap.
* **Processing:** Saturation, Soft-clipping, Resonant Filter, VCA.

## 🚀 Installation & Build

1. **Prerequisites:** Arduino IDE with DaisyDuino support.

2. **Wiring:** See the `/schematics` folder for CD4051 connections.
3. **Flash:** Upload `TR-DZ_V5.1.ino` to your Daisy Seed.

## 🗺️ Roadmap

-  [x] Analog input stabilization (Hysteresis/Smoothing).

- [x] Dual-Envelope audio engine.

- [ ] Euclidean Sequencing implementation.

- [ ] Snapshot (Preset) saving.

- [ ] Brushed aluminum chassis design.

## 🤝 Contribution

Sound design and DSP optimization ideas are welcome. Feel free to open an issue or submit a pull request.

---
*Developed by D.ZIF*
