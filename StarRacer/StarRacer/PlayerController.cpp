#include "pch.h"
#include "glut.h"
#include <stdlib.h>
#include "PlayerController.h"


PlayerController::PlayerController()
{
	Reset();
}

PlayerController::~PlayerController()
{
}

void PlayerController::HandleInput(int key, int xx, int yy)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		Horizontal = TernaryState::TNegtive;
		break;
	case GLUT_KEY_RIGHT:
		Horizontal = TernaryState::TPositive;
		break;
	case GLUT_KEY_DOWN:
		Forward = TernaryState::TNegtive;
		break;
	case GLUT_KEY_UP:
		Forward = TernaryState::TPositive;
		break;
	case GLUT_KEY_PAGE_DOWN:
		Vertical = TernaryState::TNegtive;
		break;
	case GLUT_KEY_PAGE_UP:
		Vertical = TernaryState::TPositive;
		break;
	default:
		break;
	}
}

void PlayerController::HandleInput(unsigned char key, int xx, int yy)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'a':
		Rotation.y = TernaryState::TNegtive;
		break;
	case 'd':
		Rotation.y = TernaryState::TPositive;
		break;
	case 'w':
		Rotation.x = TernaryState::TNegtive;
		break;
	case 's':
		Rotation.x = TernaryState::TPositive;
		break;
	case 'q':
		Rotation.z = TernaryState::TNegtive;
		break;
	case 'e':
		Rotation.z = TernaryState::TPositive;
		break;
	case ' ':
		Brake = BinaryState::BPositive;
		break;
	default:
		break;
	}
}

void PlayerController::Reset()
{
	Rotation = { TernaryState::TNutrual,
		   TernaryState::TNutrual,
		   TernaryState::TNutrual };
	Forward = TernaryState::TNutrual;
	Horizontal = TernaryState::TNutrual;
	Vertical = TernaryState::TNutrual;
	Brake = BinaryState::BNegative;
}
