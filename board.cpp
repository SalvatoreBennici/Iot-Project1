#include "board.h"

short unsigned int brightness = 0;
short unsigned int fadeAmount = 5;

short unsigned int ledPin[] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN};
short unsigned int buttonsPins [] = {BUTTON1_PIN, BUTTON2_PIN, BUTTON3_PIN, BUTTON4_PIN};

short unsigned int buttonsStates [] = {false, false, false, false};
short unsigned int buttonsCurrentStates [] = {LOW, LOW, LOW, LOW};
short unsigned int buttonsLastStates [] = {LOW, LOW, LOW, LOW};


void boardSetup(){
  for(int i = 0; i < 4; i++) {
    pinMode(ledPin[i], OUTPUT);
  }
  pinMode(buttonsPins[0], INPUT_PULLUP);
}

void checkButtonsPressed() {
  for(int i = 0; i < 4; i++) {
    buttonsCurrentStates[i] = digitalRead(buttonsPins[i]);
    if(buttonsLastStates[i] == LOW && buttonsCurrentStates[i] == HIGH) {
      buttonsStates[i] = true;
    } else {
      buttonsStates[i] = false;
    }
    buttonsLastStates[i] = buttonsCurrentStates[i];
  }
}

unsigned short int readDifficultyLevel() {
  return (unsigned short int)(analogRead(POT_PIN) / 128) + 1;
}

void pulsingLed(int ledPin) {
  analogWrite(ledPin, brightness);
  // Change the brightness for the next time
  brightness += fadeAmount;
  // Reverse the direction of the fading at the ends of the fade
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  delay(15);
}

void pinInterrupt(void) {
}

void enterSleep(void) {
  digitalWrite(LED_RED_PIN, LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), pinInterrupt, FALLING);
  
  sleep_mode();
  /* Il programma riprende qui. */
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(BUTTON1_PIN));

}

bool getButtonState (int i) {
  return buttonsStates[i];
}

bool isSomeButtonPressed(){
  for(int i = 0; i < 4; i++){
    if(buttonsStates[i]){
      return true;
    }
  }
  return false;
}

void setLedState(unsigned short int ledNumber, unsigned short int value) {
  digitalWrite(ledPin[ledNumber], value);
}

void clearAllLed() {
  for(int i = 0; i < 4; i++) {
    setLedState(i, LOW);
  }
}
