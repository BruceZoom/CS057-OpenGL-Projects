#include "pch.h"
#include "Galaxy.h"

#pragma region Galaxy

Galaxy::Galaxy(int num_star, string textures[])
{
	this->num_star = num_star;
	this->stars = new Star[num_star];
	textPic = new GLuint[num_star];
	glGenTextures(num_star, textPic);

	for (int i = 0; i < num_star; i++) {
		glBindTexture(GL_TEXTURE_2D, textPic[i]);
		ppic = ZXCLoadBMP(textures[i].c_str());
		glPixelStoref(GL_UNPACK_ALIGNMENT, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, ppic->iwidth, ppic->iheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, ppic->pByte);
		free(ppic->pByte);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
}

Galaxy::Galaxy(int num_star, string textures[], Star stars[])
{
	this->num_star = num_star;
	this->stars = new Star[num_star];
	textPic = new GLuint[num_star];
	glGenTextures(num_star, textPic);

	for (int i = 0; i < num_star; i++) {
		glBindTexture(GL_TEXTURE_2D, textPic[i]);
		ppic = ZXCLoadBMP(textures[i].c_str());
		glPixelStoref(GL_UNPACK_ALIGNMENT, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, ppic->iwidth, ppic->iheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, ppic->pByte);
		free(ppic->pByte);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

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

void Galaxy::SetStar(int idx, BallTransform star)
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
	glRotatef(stars[idx].transform.rotateDegree,
			  stars[idx].transform.axis.x,
			  stars[idx].transform.axis.y,
			  stars[idx].transform.axis.z);
	DrawSphere(0, 0, 0, stars[idx].transform.radius);
}

void Galaxy::UpdateStar(int idx)
{
	stars[idx].transform.rotateDegree += 0.5;
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
