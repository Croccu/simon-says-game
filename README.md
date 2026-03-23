# Simon Says — NeoPixel Edition

A classic Simon Says memory game built for the Arduino Uno using WS2812B (NeoPixel) LEDs, buttons, and a piezo buzzer.

## How It Works

The game lights up LEDs in a random sequence (with matching tones) that grows by one step each round. The player must repeat the sequence by pressing the corresponding buttons. A wrong press triggers a fail animation and resets the game. Survive all 32 rounds to win.

## Hardware

- **Arduino Uno** (or compatible)
- **4× WS2812B / NeoPixel LEDs** — data in on pin **D6**
- **4× Momentary push buttons** — pins **D2–D5** (wired to GND, using internal pull-ups)
- **1× Passive piezo buzzer** — pin **D9**

### Wiring Summary

| Component | Pin |
|-----------|-----|
| NeoPixel DIN | D6 |
| Button 0 (Red) | D2 |
| Button 1 (Green) | D3 |
| Button 2 (Blue) | D4 |
| Button 3 (Yellow) | D5 |
| Buzzer | D9 |

Each button connects its pin to GND when pressed; `INPUT_PULLUP` is used so no external resistors are needed.

## Dependencies

- [Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel)

Install via the Arduino IDE Library Manager: search for **Adafruit NeoPixel**.

## Upload

1. Open `simon_says_neopixel.ino` in the Arduino IDE.
2. Select **Board → Arduino Uno** and the correct serial port.
3. Click **Upload**.

## LED Colors & Tones

| Index | Color  | Frequency |
|-------|--------|-----------|
| 0     | Red    | 440 Hz    |
| 1     | Green  | 554 Hz    |
| 2     | Blue   | 659 Hz    |
| 3     | Yellow | 784 Hz    |

## License

This project is provided as-is for educational and hobbyist use.
