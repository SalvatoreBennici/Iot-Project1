#include <math.h>
#include "Arduino.h"
#include "board.h"

#define GAME_WAITING 1
#define GAME_RUNNING 2
#define GAME_OVER 3

extern short unsigned int gameState;

void gameWaiting();

void gameRunning();

void gameOver();

bool isPlayerReady();

void setDifficultyLevel();

void checkSleepMode();

void moveBall();

bool isBallCatched();

void goToNextLevel();

void elaborateDifficulty();

void resetGame();