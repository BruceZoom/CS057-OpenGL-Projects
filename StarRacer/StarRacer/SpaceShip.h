#pragma once

#include "glut.h"
#include "Utils.h"
#include "PlayerController.h"

#define BODY_TEXTURE    0
#define GLASS_TEXTURE   1

using namespace std;

// Thunderbird body
extern short face_indiciesBody[3704][9];
extern GLfloat verticesBody[1898][3];
extern GLfloat normalsBody[2716][3];
extern GLfloat texturesBody[2925][2];

// Glass cock-pit
extern short face_indiciesGlass[352][9];
extern GLfloat verticesGlass[197][3];
extern GLfloat normalsGlass[227][3];
extern GLfloat texturesGlass[227][2];

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
	GLuint textures[2];
	GLuint bodyList;
	GLuint glassList;
	void DrawBody();
	void DrawGlass();
public:
	SpaceShip(Vector3 initPosition, float th=0.0005);
	~SpaceShip();
	void DrawSpaceShip();
	void UpdateSpaceShip(const PlayerController &controller);
};
