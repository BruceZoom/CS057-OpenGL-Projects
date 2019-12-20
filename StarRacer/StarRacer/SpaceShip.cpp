#include "pch.h"
#include <cmath>
#include "glut.h"
#include "SpaceShip.h"
#include "BMPLoad.h"


SpaceShip::SpaceShip(Vector3 initPosition, float th):RoundThreshold(th)
{
	GLint iWidth, iHeight, iComponents;
	GLenum eFormat;
	GLbyte *pBytes;

	glGenTextures(2, textures);

	// Load the body texture
	glBindTexture(GL_TEXTURE_2D, textures[BODY_TEXTURE]);
	pBytes = gltLoadTGA("textures/body.tga", &iWidth, &iHeight, &iComponents, &eFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, (void *)pBytes);
	free(pBytes);
	GLfloat fLargest;
	//glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
	glGetFloatv(0x84FF, &fLargest);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
	glTexParameterf(GL_TEXTURE_2D, 0x84FE, fLargest);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D, textures[GLASS_TEXTURE]);
	pBytes = gltLoadTGA("textures/glass.tga", &iWidth, &iHeight, &iComponents, &eFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, (void *)pBytes);
	free(pBytes);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// gllist
	bodyList = glGenLists(2);
	glassList = bodyList + 1;

	glNewList(bodyList, GL_COMPILE);
	DrawBody();
	glEndList();

	glNewList(glassList, GL_COMPILE);
	DrawGlass();
	glEndList();

	// initialize transform
	position = initPosition;
	forward = unitZ;
	up = unitY;
	right = unitX;
	translationSpeed = zero;
	rotationSpeed = zero;
	translationAcc = { 0.003, 0.003, 0.005 };
	rotationAcc = { 0.003, 0.003, 0.003 };
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::DrawSpaceShip()
{

	Vector3 model_pos = {
		position.x + forward.x / 2,
		position.y + forward.y / 2 - 0.1,
		position.z + forward.z / 2
	};
	//glTranslatef(model_pos.x, model_pos.y, model_pos.z);
	//gluLookAt(model_pos.x, model_pos.y, model_pos.z,
	//	model_pos.x + forward.x, model_pos.y + forward.y, model_pos.z + forward.z,
	//	up.x, up.y, up.z);
	glPushMatrix();
	{
		glTranslatef(0, -0.1, -0.4);
		glRotatef(180, 0, 1, 0);
		//glRotatef(-asin(forward.y) * 180 / PI, 1, 0, 0);
		//glRotatef(asin(forward.x / sqrt(forward.x * forward.x + forward.z * forward.z)) * 180 / PI, 0, 1, 0);
		glPushMatrix();
		{
			//gluLookAt(0, 0, 0, 0, 0, 1, 0, 1, 0);
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			glBindTexture(GL_TEXTURE_2D, textures[BODY_TEXTURE]);
			glScalef(.002, .002, .002);
			glCallList(bodyList); //DrawBody();
		}
		glPopMatrix();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(0.0f, 0.0132f, 0.0555f);
		glBindTexture(GL_TEXTURE_2D, textures[GLASS_TEXTURE]);

		glScalef(0.002, 0.002, 0.002);
		//    glFrontFace(GL_CW);
		//    glCallList(glassList); //DrawGlass();
		glFrontFace(GL_CCW);
		glCallList(glassList); //DrawGlass();
		glDisable(GL_BLEND);
	}
	glPopMatrix();
	////glScalef(1/0.002, 1/0.002, 1/0.002);
	//glTranslatef(model_pos.x, model_pos.y, model_pos.z);

	gluLookAt(position.x, position.y, position.z,
		position.x + forward.x, position.y + forward.y, position.z + forward.z,
		up.x, up.y, up.z);
}

void SpaceShip::UpdateSpaceShip(const PlayerController & controller)
{
	// update rotate speed
	rotationSpeed.x -= (controller.Rotation.x - 1) * rotationAcc.x;
	rotationSpeed.y -= (controller.Rotation.y - 1) * rotationAcc.y;
	rotationSpeed.z -= (controller.Rotation.z - 1) * rotationAcc.z;

	// update translate speed
	translationSpeed = translationSpeed.EltWiseAdd(
		forward.SclMul((controller.Forward - 1) * translationAcc.z)
	).EltWiseAdd(
		right.SclMul(-(controller.Horizontal - 1) * translationAcc.x)
	).EltWiseAdd(
		up.SclMul(-(controller.Vertical - 1) * translationAcc.y)
	);

	// brake
	if (controller.Brake == BinaryState::BPositive) {
		translationSpeed.z /= 2;
		translationSpeed.x /= 2;
		translationSpeed.y /= 2;
		rotationSpeed.x /= 2;
		rotationSpeed.y /= 2;
		rotationSpeed.z /= 2;
	}

	// small value round to zero
	RoundZero(rotationSpeed.x, RoundThreshold);
	RoundZero(rotationSpeed.y, RoundThreshold);
	RoundZero(rotationSpeed.z, RoundThreshold);
	if (translationSpeed.Norm() < RoundThreshold) {
		translationSpeed = zero;
	}

	// update local system
	float tmp = PI / 180;
	float tx = tan(rotationSpeed.x * tmp);
	float ty = tan(rotationSpeed.y * tmp);
	float tz = tan(rotationSpeed.z * tmp);
	Vector3 _up = up.EltWiseAdd(forward.SclMul(-tx)).EltWiseAdd(right.SclMul(tz)).Normalize();
	Vector3 _forward = forward.EltWiseAdd(up.SclMul(tx)).EltWiseAdd(right.SclMul(ty)).Normalize();
	Vector3 _right = right.EltWiseAdd(up.SclMul(-tz)).EltWiseAdd(forward.SclMul(-ty)).Normalize();
	up = _up;
	forward = _forward;
	right = _right;
	
	// update global position
	position = position.EltWiseAdd(translationSpeed);
}
