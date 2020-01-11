#pragma once
#include <vector>

using namespace std;

static class GameController
{
private:
	static float currentTimeElapsed;
	static vector<float> timeElapsedVector;
	static int deathCount;
	const static int MaxLapsDisplayed = 10;
public:
	GameController();
	~GameController();
	static void OnDeath();
	static void UpdateTime(float seconds);
	static void TrackPassed();
	static void DrawUI();
};

