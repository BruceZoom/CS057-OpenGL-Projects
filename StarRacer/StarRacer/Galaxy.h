#pragma once
#include <string>
#include "glut.h"
#include "Utils.h"
#include "BMPLoad.h"
#include "CollisionSystem.h"

using namespace std;

class Star{
public:
	SphereTransform transform;
	Vector3 rotateAxis = { 0, 1, 0 };
	float rotateDegree = 0;
	float rotateSpeed = 0;
	Vector3 revolveCenter = { 0, 0, 0 };	// the revolve plane can only be the x-z plane
	float revolveDegree = 0;
	float revolveRadius = 0;
	float revolveSpeed = 0;
	SphereCollider collider;
	Star():collider(transform.position, transform.radius, this, Tag::TStar) {};
};

class Galaxy
{
	int num_star;
	GLuint * textPic;
	Star * stars;
	void BindTexture(int idx, string textureFile);
public:
	Galaxy(int num_star, string filename);
	Galaxy(int num_star, string textures[]);
	Galaxy(int num_star, string textures[], Star stars[]);
	~Galaxy();
	void SetStar(int idx, float x, float y, float z, float r);
	void SetStar(int idx, SphereTransform star);
	void SetStar(int idx, Star star);
	void DrawStar(int idx);
	void UpdateStar(int idx);
	void DrawGalaxy();
};

