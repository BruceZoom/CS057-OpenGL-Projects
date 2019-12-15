#pragma once
#include "Utils.h"

using namespace std;

enum BinaryState { BNegative, BPositive };

enum TernaryState { TNegtive, TNutrual, TPositive };

class PlayerController
{
public:
	Vector3 Rotation;
	TernaryState Forward;
	TernaryState Horizontal;
	TernaryState Vertical;
	BinaryState Brake;
	PlayerController();
	~PlayerController();
	void HandleInput(int key, int xx, int yy);
	void HandleInput(unsigned char key, int xx, int yy);
	void Reset();
};

