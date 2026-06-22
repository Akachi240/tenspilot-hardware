#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ============================================
// TENSPilot+ OPTIMIZED FOR ARDUINO UNO
// TRUE BIPHASIC EDITION - CLINICALLY CALIBRATED
// ============================================

LiquidCrystal_I2C lcd(0x27, 20, 4);

// ============================================
// HARDWARE PINS
// ============================================
#define POT_FREQ    A0
#define POT_WIDTH   A1
#define POT_LEVEL   A2
#define BTN_MODE    2

#define LED_GENERAL     12
#define LED_NEUROPATHY  7
#define LED_PERIOD      11  
#define LED_MUSCLE      5
#define LED_DRIVER_ON   4

// BIPHASIC DRIVER PINS
const int IN1 = 8;
const int IN2 = 9;
const int ENA = 10; // Controls Intensity via PWM

// ============================================
// MODE DEFINITIONS & CLINICAL PARAMETERS
// ============================================
#define MODE_GENERAL    0
#define MODE_NEUROPATHY 1
#define MODE_PERIOD     2
#define MODE_MUSCLE     3
#define NUM_MODES       4

// Research-backed ranges based on target nerve fiber recruitment
const byte freqMin[NUM_MODES] PROGMEM  = {80,   2,    90,   35};  // Hz
const byte freqMax[NUM_MODES] PROGMEM  = {120,  10,   120,  80};  // Hz
const int widthMin[NUM_MODES] PROGMEM  = {50,   200,  150,  250}; // Microseconds (us)
const int widthMax[NUM_MODES] PROGMEM  = {150,  300,  250,  400}; // Microseconds (us)

// ============================================
// GLOBAL STATE 
// ============================================
byte currentMode = 0;
int frequency = 80;
int pulseWidth = 100;
int intensity = 0;
bool deviceActive = false;

// BIPHASIC TIMING STATE
unsigned long lastPulseTime = 0;
bool isPositivePhase = true;

// POTENTIOMETER FILTERING
#define POT_SAMPLES 4
int potFreqBuffer[POT_SAMPLES];
int potWidthBuffer[POT_SAMPLES];
int potLevelBuffer[POT_SAMPLES];
byte potIndex = 0;

// BUTTON & TIMING
byte prevButtonState = 1;
unsigned long lastModeChangeTime = 0;
unsigned long lastLcdUpdate = 0;
const unsigned long MODE_DEBOUNCE = 300;
const unsigned long LCD_UPDATE = 150;

// ============================================
// SETUP
// ============================================
void setup() {
  Serial.begin(9600);
  
  // UI Pins
  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(LED_GENERAL, OUTPUT);
  pinMode(LED_NEUROPATHY, OUTPUT);
  pinMode(LED_PERIOD, OUTPUT);
  pinMode(LED_MUSCLE, OUTPUT);
  pinMode(LED_DRIVER_ON, OUTPUT);
  
  
  // Driver Pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  
  // LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(F("TENSPilot+ INIT"));
  delay(1000);
  lcd.clear();
  
  updateModeIndicators();
  updateLcd();
}

// ============================================
// MAIN LOOP
// ============================================
void loop() {
  unsigned long now = millis();
  
  readPotentiometers();
  checkModeButton(now);
  
  // Fire the TENS logic continuously
  updateTensPulse();
  
  // Update LCD smoothly without blocking the pulses
  if (now - lastLcdUpdate >= LCD_UPDATE) {
    updateLcd();
    lastLcdUpdate = now;
  }
}

// ============================================
// TRUE BIPHASIC PULSE ENGINE
// ============================================
void updateTensPulse() {
  if (intensity == 0 || frequency == 0) {
    // Safety off
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
    deviceActive = false;
    return;
  }

  deviceActive = true;
  unsigned long currentMicros = micros();
  unsigned long period_us = 1000000UL / frequency; // Calculate time between pulses

  if (currentMicros - lastPulseTime >= period_us) {
    lastPulseTime = currentMicros;

    // 1. Set Intensity via PWM on the Enable Pin (0-255 scale)
    int pwmValue = map(intensity, 1, 100, 50, 255); // Start at 50 to overcome motor driver threshold
    analogWrite(ENA, pwmValue);

    // 2. Fire the precisely timed Biphasic Pulse
    if (isPositivePhase) {
      digitalWrite(IN1, HIGH);
      delayMicroseconds(pulseWidth);
      digitalWrite(IN1, LOW);
    } else {
      digitalWrite(IN2, HIGH);
      delayMicroseconds(pulseWidth);
      digitalWrite(IN2, LOW);
    }
    
    // 3. Turn driver off completely between pulses
    analogWrite(ENA, 0);
    
    // 4. Flip polarity for the next pulse
    isPositivePhase = !isPositivePhase;
  }
}

// ============================================
// BUTTON HANDLING
// ============================================
void checkModeButton(unsigned long now) {
  byte buttonState = digitalRead(BTN_MODE);
  if (buttonState == 0 && prevButtonState == 1) {
    if ((now - lastModeChangeTime) > MODE_DEBOUNCE) {
      currentMode = (currentMode + 1) % NUM_MODES;
      updateModeIndicators();
      lastModeChangeTime = now;
    }
  }
  prevButtonState = buttonState;
}

// ============================================
// POTENTIOMETER READING
// ============================================
void readPotentiometers() {
  potFreqBuffer[potIndex] = analogRead(POT_FREQ);
  potWidthBuffer[potIndex] = analogRead(POT_WIDTH);
  potLevelBuffer[potIndex] = analogRead(POT_LEVEL);
  potIndex = (potIndex + 1) % POT_SAMPLES;
  
  long avgFreq = 0, avgWidth = 0, avgLevel = 0;
  for (byte i = 0; i < POT_SAMPLES; i++) {
    avgFreq += potFreqBuffer[i];
    avgWidth += potWidthBuffer[i];
    avgLevel += potLevelBuffer[i];
  }
  avgFreq /= POT_SAMPLES;
  avgWidth /= POT_SAMPLES;
  avgLevel /= POT_SAMPLES;
  
  int fMin = pgm_read_byte(&freqMin[currentMode]);
  int fMax = pgm_read_byte(&freqMax[currentMode]);
  int wMin = pgm_read_word(&widthMin[currentMode]);
  int wMax = pgm_read_word(&widthMax[currentMode]);
  
  frequency = map(avgFreq, 0, 1023, fMin, fMax);
  pulseWidth = map(avgWidth, 0, 1023, wMin, wMax);
  intensity = map(avgLevel, 0, 1023, 0, 100);
  
  digitalWrite(LED_DRIVER_ON, intensity > 0 ? HIGH : LOW);
}

// ============================================
// UPDATE MODE LEDS
// ============================================
void updateModeIndicators() {
  digitalWrite(LED_GENERAL, LOW);
  digitalWrite(LED_NEUROPATHY, LOW);
  digitalWrite(LED_PERIOD, LOW);
  digitalWrite(LED_MUSCLE, LOW);
  
  switch(currentMode) {
    case 0: digitalWrite(LED_GENERAL, HIGH); break;
    case 1: digitalWrite(LED_NEUROPATHY, HIGH); break;
    case 2: digitalWrite(LED_PERIOD, HIGH); break;
    case 3: digitalWrite(LED_MUSCLE, HIGH); break;
  }
}

// ============================================
// LCD DISPLAY (UI/UX Upgraded)
// ============================================
void updateLcd() {
  char buffer[21]; // 20 characters + 1 null terminator

  // ROW 0: Header
  lcd.setCursor(0, 0);
  lcd.print(F("TENSPilot+          ")); // Padded to 20 chars to overwrite cleanly
  
  // ROW 1: Active Mode
  lcd.setCursor(0, 1);
  lcd.print(F("Mode: "));
  switch(currentMode) {
    case 0: lcd.print(F("GENERAL       ")); break;
    case 1: lcd.print(F("NEUROPATHY    ")); break;
    case 2: lcd.print(F("PERIOD        ")); break;
    case 3: lcd.print(F("MUSCLE        ")); break;
  }
  
  // ROW 2: Grouped Parameters (Frequency & Width)
  sprintf(buffer, "Pulse: %3dHz | %3dus", frequency, pulseWidth);
  lcd.setCursor(0, 2);
  lcd.print(buffer);
  
  // ROW 3: Intensity & Safety Status
  sprintf(buffer, "Level: %3d%%  %s", intensity, deviceActive ? "ACTIVE " : "STANDBY");
  lcd.setCursor(0, 3);
  lcd.print(buffer);
}
