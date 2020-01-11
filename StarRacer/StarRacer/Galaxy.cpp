#include "pch.h"
#include "Galaxy.h"
#include "SpaceShip.h"
#include <typeinfo>

#pragma region Galaxy

void Galaxy::BindTexture(int idx, string textureFile)
{
	BMPPic * ppic;
	glBindTexture(GL_TEXTURE_2D, textPic[idx]);
	ppic = ZXCLoadBMP(textureFile.c_str());
	glPixelStoref(GL_UNPACK_ALIGNMENT, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ppic->iwidth, ppic->iheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, ppic->pByte);
	free(ppic->pByte);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

Galaxy::Galaxy(int num_star, string filename)
{
	this->num_star = num_star;
	this->stars = new Star[num_star];
	this->textPic = new GLuint[num_star];
	glGenTextures(num_star, textPic);

	float radiusUnit = 0.1;
	float revolveRadiusUnit = 5;
	float rotateSpeedUnit = 1;
	float revolveSpeedUnit = 0.0001 * 19;

	float radius[] = { 15, 2.2, 3.5, 3.5, 2.5, 12, 11, 7.1, 7 };
	float rotateSpeed[] = { 1.0 / 30, 1.0 / 58, 1.0 / 243, 1.0 / 1, 1.0 / 1,
		1.0 / 0.4, 1.0 / 0.4, 1.0 / 0.7, 1.0 / 0.65 };
	float revolveRadius[] = { 0, 0.4, 0.7, 1.0, 1.5, 5.2, 9.5, 19.2, 30 };
	float revolveSpeed[] = { 0.0, 1.0 / 9.3, 1.0 / 15, 1.0 / 19, 1.0 / 26,
		1.0 / 63, 1.0 / 100, 1.0 / 175, 1.0 / 224 };
	char textures[][50] = {
		"Textures/sun.bmp",
		"Textures/mercury.bmp",
		"Textures/venus.bmp",
		"Textures/earth.bmp",
		"Textures/mars.bmp",
		"Textures/jupyter.bmp",
		"Textures/saturn.bmp",
		"Textures/uranus.bmp",
		"Textures/neptune.bmp",
	};

	for (int idx = 0; idx < num_star; idx++) {
		cout << idx << endl;
		BindTexture(idx, textures[idx]);
		stars[idx].transform.radius = radius[idx] * radiusUnit;
		stars[idx].rotateSpeed = rotateSpeed[idx] * rotateSpeedUnit;
		stars[idx].revolveRadius = revolveRadius[idx] * revolveRadiusUnit;
		stars[idx].revolveCenter = zero;
		stars[idx].revolveSpeed = revolveSpeed[idx] * revolveSpeedUnit;
		stars[idx].collider.SetCollider(zero, stars[idx].transform.radius);
		stars[idx].revolveDegree = rand() % 360;
		CollisionSystem::AddCollider(&stars[idx].collider);
		UpdateStar(idx);
	}
}

Galaxy::Galaxy(int num_star, string textures[])
{
	this->num_star = num_star;
	this->stars = new Star[num_star];
	textPic = new GLuint[num_star];
	glGenTextures(num_star, textPic);

	for (int i = 0; i < num_star; i++) {
		BindTexture(i, textures[i]);
	}
}

Galaxy::Galaxy(int num_star, string textures[], Star stars[])
{
	this->num_star = num_star;
	this->stars = new Star[num_star];
	this->textPic = new GLuint[num_star];
	glGenTextures(num_star, textPic);

	for (int i = 0; i < num_star; i++) {
		BindTexture(i, textures[i]);
		this->stars[i] = stars[i];
	}
}

Galaxy::~Galaxy()
{
	delete textPic;
	delete stars;
}

#pragma region Star

void Galaxy::SetStar(int idx, float x, float y, float z, float r)
{
	stars[idx].transform.position.x = x;
	stars[idx].transform.position.y = y;
	stars[idx].transform.position.z = z;
	stars[idx].transform.radius = r;
}

void Galaxy::SetStar(int idx, SphereTransform star)
{
	stars[idx].transform = star;
}

void Galaxy::SetStar(int idx, Star star)
{
	stars[idx] = star;
}

void Galaxy::DrawStar(int idx)
{
	glBindTexture(GL_TEXTURE_2D, textPic[idx]);
	glTranslatef(stars[idx].transform.position.x,
				 stars[idx].transform.position.y,
				 stars[idx].transform.position.z);
	glRotatef(stars[idx].rotateDegree,
			  stars[idx].rotateAxis.x,
			  stars[idx].rotateAxis.y,
			  stars[idx].rotateAxis.z);
	// manually decide resolution
	if (stars[idx].transform.radius /
		PlayerController::playerLocation->EltWiseAdd(
			stars[idx].transform.position.SclMul(-1)).Norm() > 0.5) {
		DrawSphere(0, 0, 0, stars[idx].transform.radius, 40, 60);
	}
	else if (stars[idx].transform.radius /
		PlayerController::playerLocation->EltWiseAdd(
			stars[idx].transform.position.SclMul(-1)).Norm() > 0.03) {
	DrawSphere(0, 0, 0, stars[idx].transform.radius, 25, 45);
	}
	else if (stars[idx].transform.radius /
		PlayerController::playerLocation->EltWiseAdd(
			stars[idx].transform.position.SclMul(-1)).Norm() > 0.005) {
		DrawSphere(0, 0, 0, stars[idx].transform.radius, 10, 20);
	}
}

void Galaxy::UpdateStar(int idx)
{
	stars[idx].rotateDegree += stars[idx].rotateSpeed;
	stars[idx].revolveDegree += stars[idx].revolveSpeed;
	stars[idx].transform.position = {
		stars[idx].revolveCenter.x +
		cos(stars[idx].revolveDegree) * stars[idx].revolveRadius,
		stars[idx].revolveCenter.y,
		stars[idx].revolveCenter.z +
		sin(stars[idx].revolveDegree) * stars[idx].revolveRadius,
	};
	SphereCollider* other = stars[idx].collider.Update(stars[idx].transform.position);
	if (other != NULL) {
		if (other->tag == Tag::TShip) {
			printf("SpaceShip collide.\n");
		}
	}
}

void Galaxy::UpdateGalaxy()
{
	for (int i = 0; i < num_star; i++) {
		UpdateStar(i);
	}
}

#pragma endregion

void Galaxy::DrawGalaxy()
{
	for (int i = 0; i < num_star; i++) {
		glPushMatrix();
		DrawStar(i);
		glPopMatrix();
	}
}

#pragma endregion

