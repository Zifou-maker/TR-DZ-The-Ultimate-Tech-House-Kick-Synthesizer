# 🔌 Wiring Guide - TR-DZ v13

This document details the physical connections for the **TR-DZ v13**.
This version uses an **Electro-Smith Daisy Seed** coupled with a **CD74HC4067 Analog Multiplexer** to manage 8 potentiometers via a single analog input.

> ⚠️ **CRITICAL CHANGE IN V13**
> The Multiplexer address pins have been moved from pins `D0-D3` to **`D3-D6`**.
> This change improves USB Serial stability and prevents conflicts.
> **Please verify your wiring before powering on.**

---

## 🛠 Component List

* **Brain:** 1x Electro-Smith Daisy Seed (v1.1 or v1.2)
* **Expansion:** 1x CD74HC4067 (16-Channel Analog Multiplexer)
* **Display:** 1x OLED Display I2C (SH1106 or SSD1306)
* **Controls:** 8x Potentiometers (10k Linear recommended)
* **Input:** 1x Push Button (Momentary)
* **Misc:** Breadboard, Jumper wires.

---

## 📍 Pinout Configuration

### 1. Multiplexer (CD74HC4067) to Daisy Seed

This is the core of the control system. Ensure the power supply is correct to avoid noise.

| Mux Pin | Daisy Seed Pin | Function |
| :--- | :--- | :--- |
| **VCC** | **3V3 (Pin 38)** | Power 3.3V (Digital) |
| **GND** | **DGND (Pin 40)** | Digital Ground |
| **SIG (Z)** | **A0 (Pin 16)** | Analog Signal Input (Read) |
| **S0** | **D3** | Address Bit 0 |
| **S1** | **D4** | Address Bit 1 |
| **S2** | **D5** | Address Bit 2 |
| **S3** | **D6** | Address Bit 3 |
| **EN** | **GND** | Enable (Must be grounded to active) |

*(Refer to your CD74HC4067 datasheet for specific pin layout)*

### 2. OLED Display (I2C)

| OLED Pin | Daisy Seed Pin | Note |
| :--- | :--- | :--- |
| **VCC** | **3V3 (Pin 38)** | Power |
| **GND** | **DGND (Pin 40)** | Ground |
| **SCL** | **D12** | I2C Clock |
| **SDA** | **D11** | I2C Data |

### 3. Controls & Audio

| Component | Daisy Seed Pin | Note |
| :--- | :--- | :--- |
| **Button** | **D28** | The other leg connects to **GND** |
| **Audio OUT L** | **Audio Out 1** | To Jack Tip (Left) |
| **Audio OUT R** | **Audio Out 2** | To Jack Ring (Right) |
| **Audio GND** | **AGND (Pin 20)** | To Jack Sleeve (Audio Ground) |

---

## 🎛 Potentiometer Mapping (v13)

Potentiometers are connected to inputs **C0 through C7** on the Multiplexer.
Connect the center pin (Wiper) of the pot to the Mux. The outer pins connect to 3V3 and GND.

| Mux Channel | Parameter | Description |
| :--- | :--- | :--- |
| **C0** | **BPM** | Global Tempo (60 - 200 BPM) |
| **C1** | **Kick Decay** | Kick Length (Short -> Long Boom) |
| **C2** | **Cutoff** | Master Low-Pass + Bass Filter |
| **C3** | **Resonance** | Bass Resonance (Acid Factor) |
| **C4** | **Snare Tone** | Body vs Noise Balance |
| **C5** | **Hat Vol** | Hi-Hat Volume Level |
| **C6** | **Swing** | Groove Amount (0% -> 25%) |
| **C7** | **Drive** | Master Saturation (Soft Clip) |

> **Note:** Channels C8 to C15 are unused in v13. Connect them to GND if you experience digital noise, otherwise leave them floating.

---

## ⚡️ Troubleshooting Tips

1.  **Screen stays black?** Check that you are using pins D11/D12 and not D13/D14. Verify if your code uses `U8G2_SH1106` or `U8G2_SSD1306` depending on your model.
2.  **Pots controlling the wrong parameter?** You likely swapped the S0-S3 wires. Verify: S0->D3, S3->D6.
3.  **Digital noise in audio?** Ensure your Audio Jack ground is connected to **AGND** (Pin 20) and not DGND.
