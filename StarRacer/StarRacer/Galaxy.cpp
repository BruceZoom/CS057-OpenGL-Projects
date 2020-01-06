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

	BindTexture(0, "Textures/mars.bmp");
	stars[0].transform.radius = 1.02;
	stars[0].rotateSpeed = 0.5;
	stars[0].revolveRadius = 5;
	stars[0].revolveCenter = zero;
	stars[0].revolveSpeed = 0.002;
	stars[0].collider.SetCollider(zero, stars[0].transform.radius);
	CollisionSystem::AddCollider(&stars[0].collider);
	UpdateStar(0);

	BindTexture(1, "Textures/earth.bmp");
	stars[1].transform.radius = 1;
	stars[1].rotateSpeed = 0.6;
	stars[1].revolveRadius = 3;
	stars[1].revolveDegree = 45;
	stars[1].revolveCenter = zero;
	stars[1].revolveSpeed = 0.003;
	stars[0].collider.SetCollider(zero, stars[1].transform.radius);
	CollisionSystem::AddCollider(&stars[1].collider);
	UpdateStar(1);

	BindTexture(2, "Textures/venus.bmp");
	stars[2].transform.radius = 0.3;
	stars[2].rotateSpeed = 0.7;
	stars[2].revolveRadius = 1.5;
	stars[2].revolveCenter = zero;
	stars[2].revolveSpeed = 0.004;
	stars[0].collider.SetCollider(zero, stars[2].transform.radius);
	CollisionSystem::AddCollider(&stars[2].collider);
	UpdateStar(2);
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
	DrawSphere(0, 0, 0, stars[idx].transform.radius);
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

