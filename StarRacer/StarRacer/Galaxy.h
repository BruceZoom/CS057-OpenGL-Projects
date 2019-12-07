#pragma once
#include <string>
#include "glut.h"
#include "Utils.h"
#include "BMPLoad.h"

using namespace std;

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

