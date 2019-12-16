#pragma once

#include "Utils.h"
#include "PlayerController.h"

using namespace std;

class SpaceShip
{
	Vector3 position;
	Vector3 forward;
	Vector3 up;
	Vector3 right;
	Vector3 translationSpeed;
	Vector3 rotationSpeed;
	Vector3 translationAcc;
	Vector3 rotationAcc;
	const float RoundThreshold;
public:
	SpaceShip(Vector3 initPosition, float th=0.0005);
	~SpaceShip();
	void DrawSpaceShip();
	void UpdateSpaceShip(const PlayerController &controller);
};

