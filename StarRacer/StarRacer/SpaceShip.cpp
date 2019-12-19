#include "pch.h"
#include <cmath>
#include "glut.h"
#include "SpaceShip.h"


SpaceShip::SpaceShip(Vector3 initPosition, float th):RoundThreshold(th)
{
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
	gluLookAt(position.x, position.y, position.z,
		position.x + forward.x, position.y + forward.y, position.z + forward.z,
		up.x, up.y, up.z);

	//glPushMatrix();
	//// TODO: draw ship
	//glPopMatrix();
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
