#include "GameController.h"


float GameController::currentTimeElapsed = 0;
vector<float> GameController::timeElapsedVector = {};
int GameController::deathCount = 0;

GameController::GameController()
{
}


GameController::~GameController()
{
}

void GameController::OnDeath()
{
	deathCount += 1;
}

void GameController::UpdateTime(float seconds)
{
	currentTimeElapsed += seconds;
}

void GameController::TrackPassed()
{
	timeElapsedVector.push_back(currentTimeElapsed);
	currentTimeElapsed = 0;
}
