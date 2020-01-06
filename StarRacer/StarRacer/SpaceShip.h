#pragma once

#include "glut.h"
#include "Utils.h"
#include "PlayerController.h"
#include "3ds.h"
#include "CollisionSystem.h"

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
	Vector3 pose;
	const Vector3 pose_limit = { 10, 10, 10 };
	GLuint textures[2];
	GLuint bodyList;
	GLuint glassList;
	SphereCollider collider;
	void DrawBody();
	void DrawGlass();
	void Reset(Vector3 position);
public:
	SpaceShip(Vector3 initPosition);
	~SpaceShip();
	void DrawSpaceShip();
	void UpdateSpaceShip(const PlayerController &controller);
	void OnCollision();
};
