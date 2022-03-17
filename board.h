#include <avr/sleep.h>
#include <avr/power.h>
#include "Arduino.h"

#define LED1_PIN 7
#define LED2_PIN 8
#define LED3_PIN 9
#define LED4_PIN 10
#define LED_RED_PIN 11
#define POT_PIN A0

void checkButtonsPressed();

unsigned short int readDifficultyLevel();

void pulsingLed(int ledPin);

void pinInterrupt(void);

void enterSleep(void);

bool getButtonState(int i);

bool isSomeButtonPressed();

void setLedState(unsigned short int ledPin, unsigned short int value);

void clearAllLed();
