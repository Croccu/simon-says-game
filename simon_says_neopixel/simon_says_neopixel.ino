// Simon Says game for Arduino Uno
// Hardware: 4x WS2812B/NeoPixel (on one strip), 4x buttons, 1x passive piezo buzzer
// NeoPixel DIN -> D6, buttons -> D2..D5 (to GND, INPUT_PULLUP), buzzer -> D9

#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN   6
#define NUM_PIXELS     4

const int buttonPins[4] = {2, 3, 4, 5};
const int buzzerPin      = 9;

const int maxSequenceLength = 32;
int sequence[maxSequenceLength];
int sequenceLength = 1;

Adafruit_NeoPixel strip(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

uint32_t colors[4];

void playSequence();
bool readAndCheckPlayerInput();
int  waitForButtonPress();
void showPixel(int index, uint32_t color, int durationMs);
void clearPixels();
void playFailAnimation();
void playWinAnimation();
void startupAnimation();

void setup() {
  strip.begin();
  strip.show();

  colors[0] = strip.Color(150,   0,   0); // red
  colors[1] = strip.Color(  0, 150,   0); // green
  colors[2] = strip.Color(  0,   0, 150); // blue
  colors[3] = strip.Color(150, 150,   0); // yellow

  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  randomSeed(analogRead(A0));

  startupAnimation();
}

void loop() {
  sequence[sequenceLength - 1] = random(0, 4);

  playSequence();

  bool success = readAndCheckPlayerInput();

  if (!success) {
    playFailAnimation();
    sequenceLength = 1;
    delay(1000);
  } else {
    sequenceLength++;

    if (sequenceLength > maxSequenceLength) {
      playWinAnimation();
      sequenceLength = 1;
    }

    delay(600);
  }
}

void playSequence() {
  delay(400);

  for (int i = 0; i < sequenceLength; i++) {
    int idx = sequence[i];
    showPixel(idx, colors[idx], 350);
    delay(150);
  }
}

bool readAndCheckPlayerInput() {
  for (int i = 0; i < sequenceLength; i++) {
    int expected = sequence[i];
    int pressed  = waitForButtonPress();

    if (pressed != expected) {
      return false;
    }
  }
  return true;
}

int waitForButtonPress() {
  while (true) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(buttonPins[i]) == LOW) {
        showPixel(i, colors[i], 250);

        while (digitalRead(buttonPins[i]) == LOW) {
          delay(5);
        }
        delay(50);

        return i;
      }
    }
  }
}

void showPixel(int index, uint32_t color, int durationMs) {
  int freq;
  switch (index) {
    case 0: freq = 440; break;
    case 1: freq = 554; break;
    case 2: freq = 659; break;
    default: freq = 784; break;
  }

  clearPixels();
  strip.setPixelColor(index, color);
  strip.show();

  tone(buzzerPin, freq, durationMs);
  delay(durationMs);

  clearPixels();
}

void clearPixels() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    strip.setPixelColor(i, 0);
  }
  strip.show();
}

void playFailAnimation() {
  for (int k = 0; k < 3; k++) {
    for (int i = 0; i < NUM_PIXELS; i++) {
      strip.setPixelColor(i, strip.Color(150, 0, 0));
    }
    strip.show();
    tone(buzzerPin, 200, 300);
    delay(300);

    clearPixels();
    delay(200);
  }
}

void playWinAnimation() {
  for (int k = 0; k < 3; k++) {
    for (int i = 0; i < NUM_PIXELS; i++) {
      strip.setPixelColor(i, strip.Color(0, 150, 0));
      strip.show();
      tone(buzzerPin, 600 + i * 150, 150);
      delay(150);
    }

    clearPixels();
    delay(200);
  }
}

void startupAnimation() {
  for (int i = 0; i < 4; i++) {
    showPixel(i, colors[i], 200);
    delay(80);
  }
  clearPixels();
}
