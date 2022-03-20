#include "game_logics.h"

short unsigned int gameState;
short unsigned int difficultyLevel = 1;

short unsigned int score = 0;
short unsigned int level = 1;

long int sleepTime = 0;
long int prevTime = 0;
long int timeStep = 0;

short unsigned int ballPos = 1;
short unsigned int step = -1;

void gameOver() {
  Serial.print("Game Over. Final Score:\t");
  Serial.println(score);
  delay(200);
  resetGame();
  Serial.println("Welcome to the Catch the Bouncing Led Ball Game. Press Key T1 to Start");
  gameState = GAME_WAITING;
}

void gameWaiting() {
  pulsingLed(LED_RED_PIN);
  setDifficultyLevel();
  if(isPlayerReady()) {
    gameState = GAME_RUNNING;
    Serial.println("Go!");
    digitalWrite(LED_RED_PIN, LOW);
    sleepTime = 0;
    prevTime = 0;
    elaborateDifficulty();
  }
  checkSleepMode();
}

void gameRunning() {
  moveBall();
  if(isSomeButtonPressed()) {
    if(isBallCatched()){
      goToNextLevel();
      prevTime = timeStep;
    } else {
      gameState = GAME_OVER;
    }
  }
}

void moveBall() {
  if(millis() - prevTime >= timeStep){
    setLedState(ballPos, LOW);
    ballPos += step;
    if (ballPos <= 0 || ballPos >= 3) {
      step = -step;
    }
    setLedState(ballPos, HIGH);

    prevTime = millis();
  }
}

bool isBallCatched() {
  return getButtonState(ballPos);
}

void goToNextLevel() {
  level++;
  score++;
  Serial.print("New point! Score:\t");
  Serial.println(score);
  elaborateDifficulty();
}

void elaborateDifficulty(){
  timeStep = 3000 * exp(-((double)difficultyLevel/5) -((double)level/7)); // a * exp[-(x/b) -(y/c)]
}

bool isPlayerReady() {
  return getButtonState(0);
}

void setDifficultyLevel() {
  short unsigned int tmpDiffLvl = readDifficultyLevel();
  if(difficultyLevel != tmpDiffLvl) {
    difficultyLevel = tmpDiffLvl;
    sleepTime = 0;
    Serial.print("Difficulty set to:\t");
    Serial.println(difficultyLevel);
  }
}

void checkSleepMode() {
  if(sleepTime == 0) {
    sleepTime = millis();
  } else if(millis() - sleepTime >= 10000){
    enterSleep();
    sleepTime = 0;
  }
  if(isSomeButtonPressed()){
    sleepTime = 0;
  }  
}

void resetGame() {
  score = 0;
  level = 1;
  sleepTime = 0;
  prevTime = 0;
  timeStep = 0;
  ballPos = 1;
  step = -1;
  clearAllLed();
}

