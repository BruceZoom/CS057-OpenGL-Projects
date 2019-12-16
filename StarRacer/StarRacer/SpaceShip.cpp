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
	/*glRotatef(rotation.x, unitX.x, unitX.y, unitX.z);
	glRotatef(rotation.y, unitY.x, unitY.y, unitY.z);
	glRotatef(rotation.z, unitZ.x, unitZ.y, unitZ.z);*/
	//gluLookAt(position.x + forward.x, position.y + forward.y, position.z + forward.z,
	//	position.x, position.y, position.z,
	//	position.x + up.x, position.y + up.y, position.z + up.z);

	gluLookAt(forward.x, forward.y, forward.z,
		0, 0, 0, up.x, up.y, up.z);
	glTranslatef(position.x, position.y, position.z);

	//glPushMatrix();
	//// TODO: draw ship
	//glPopMatrix();
}

void SpaceShip::UpdateSpaceShip(const PlayerController & controller)
{
	// update translate speed
	translationSpeed.z += (controller.Forward - 1) * translationAcc.z;
	translationSpeed.x -= (controller.Horizontal - 1) * translationAcc.x;
	translationSpeed.y -= (controller.Vertical - 1) * translationAcc.y;
	
	// update rotate speed
	rotationSpeed.x -= (controller.Rotation.x - 1) * rotationAcc.x;
	rotationSpeed.y -= (controller.Rotation.y - 1) * rotationAcc.y;
	rotationSpeed.z -= (controller.Rotation.z - 1) * rotationAcc.z;

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
	RoundZero(translationSpeed.z, RoundThreshold);
	RoundZero(translationSpeed.x, RoundThreshold);
	RoundZero(translationSpeed.y, RoundThreshold);
	RoundZero(rotationSpeed.x, RoundThreshold);
	RoundZero(rotationSpeed.y, RoundThreshold);
	RoundZero(rotationSpeed.z, RoundThreshold);

	//// update rotation
	//rotation.x += rotationSpeed.x;
	//rotation.y += rotationSpeed.y;
	//rotation.z += rotationSpeed.z;
	// update position
	float tmp = PI / 180;
	float cx = cos(rotationSpeed.x * tmp), sx = sin(-rotationSpeed.x * tmp);
	float cy = cos(rotationSpeed.y * tmp), sy = sin(-rotationSpeed.y * tmp);
	float cz = cos(rotationSpeed.z * tmp), sz = sin(-rotationSpeed.z * tmp);
	Vector3 Rx[3] = { unitX, {0, cx, sx}, {0, -sx, cx} };
	Vector3 Ry[3] = { {cy, 0, -sy}, unitY, {sy, 0, cy} };
	Vector3 Rz[3] = { {cz, sz, 0}, {-sz, cz, 0}, unitZ };
	
	up = up.DotProduct(Rz).DotProduct(Ry).DotProduct(Rx).Normalize();
	right = right.DotProduct(Rz).DotProduct(Ry).DotProduct(Rx).Normalize();
	forward = forward.DotProduct(Rz).DotProduct(Ry).DotProduct(Rx).Normalize();
	
	position =
		position.EltWiseAdd(up.SclMul(translationSpeed.y)
		).EltWiseAdd(
			right.SclMul(translationSpeed.x)
		).EltWiseAdd(
			forward.SclMul(translationSpeed.z));

	////position.x += translationSpeed.x;
	//position.x += translationSpeed.DotProduct({
	//	cy * cz, -cx * sz + sx * sy * cz, sx * sz + cx * sy * cz
	//	//-cz * cy, cx * sz, cx * sy
	//	});
	////position.y += translationSpeed.y;
	//position.y += translationSpeed.DotProduct({
	//	cy * sz, cx * cz + sx * sy * sz , -sx * cz + cx * sy * sz
	//	//sz, cx * cz, -sx
	//	});
	////position.z += translationSpeed.z;
	//position.z += translationSpeed.DotProduct({
	//	-sy, sx * cy, cx * cy
	//	//cz * sy, -sx, cx * cy
	//	});
	cout << position.x << " " << position.y << " " << position.z << endl;
}
