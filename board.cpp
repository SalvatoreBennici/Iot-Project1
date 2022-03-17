#include "board.h"

short int brightness = 0;
short int fadeAmount = 5;

short unsigned int lastState = LOW;
short unsigned int currentState = LOW;

short unsigned int ledPin[] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN};

short unsigned int buttonsPins [] = {3, 4, 5, 6};
short unsigned int buttonsStates [] = {false, false, false, false};
short unsigned int buttonsCurrentStates [] = {LOW, LOW, LOW, LOW};
short unsigned int buttonsLastStates [] = {LOW, LOW, LOW, LOW};


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
  attachInterrupt(digitalPinToInterrupt(3), pinInterrupt, FALLING);
  digitalWrite(LED_RED_PIN, LOW);
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  /* Il programma riprende qui. */
  sleep_disable();

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
