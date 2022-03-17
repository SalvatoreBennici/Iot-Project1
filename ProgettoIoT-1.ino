#include "game_logics.h"
#include "board.h"

void setup() {
  Serial.begin(9600);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  pinMode(3, INPUT_PULLUP);
  Serial.println("Welcome to the Catch the Bouncing Led Ball Game. Press Key T1 to Start");
  gameState = GAME_WAITING;
}

void loop() {
  switch (gameState) {
  case GAME_WAITING:
    gameWaiting();
    break;
  case GAME_RUNNING:
    gameRunning();
    break;
  case GAME_OVER:
    gameOver();
    break;
  }
  checkButtonsPressed();
}
