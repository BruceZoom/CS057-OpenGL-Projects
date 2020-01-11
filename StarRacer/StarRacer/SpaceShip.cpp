#include "pch.h"
#include <cmath>
#include "glut.h"
#include "glaux.h"
#include "BMPLoad.h"
#include "SpaceShip.h"
#include <string>
#include "CollisionSystem.h"
#include "Track.h"
#include "GameController.h"
#include "Galaxy.h"

//  从文件中创建纹理
void CreateTexture(UINT textureArray[], LPSTR strFileName, int textureID)
{
	BMPPic * ppic;

	if (!strFileName)
		return;

	ppic = ZXCLoadBMP(strFileName);

	if (ppic == NULL)
		exit(0);

	// 生成纹理
	glGenTextures(1, &textureArray[textureID]);

	// 设置像素对齐格式
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glBindTexture(GL_TEXTURE_2D, textureArray[textureID]);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, ppic->iwidth, ppic->iheight, GL_RGB, GL_UNSIGNED_BYTE, ppic->pByte);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	if (ppic)
	{
		free(ppic->pByte);
	}
}

SpaceShip::SpaceShip(Vector3 initPosition)
{
	GLint iWidth, iHeight, iComponents;
	GLenum eFormat;
	GLbyte *pBytes;

	/* Begin 3DS Model */
	//CLoad3DS g_Load3ds;
	//t3DModel g_3DModel;
	//char model_name[] = "D:\\Bruce\\Courses\\OpenGL\\CS057-OpenGL-Projects\\StarRacer\\StarRacer\\Models\\90-intergalactic_spaceship-3ds\\Intergalactic_Spaceship-(3DS).3ds";
	//	//"Models/90-intergalactic_spaceship-3ds/Intergalactic_Spaceship-(3DS).3ds";
	//UINT g_Texture[100] = { 0 };

	//g_Load3ds.Import3DS(&g_3DModel, model_name);
	//for (int i = 0; i < g_3DModel.numOfMaterials; i++)
	//{
	//	// 判断是否是一个文件名
	//	if (strlen(g_3DModel.pMaterials[i].strFile) > 0)
	//	{
	//		//  使用纹理文件名称来装入位图
	//		printf("%s\n", g_3DModel.pMaterials[i].strFile);
	//		CreateTexture(g_Texture, g_3DModel.pMaterials[i].strFile, i);
	//	}

	//	// 设置材质的纹理ID
	//	g_3DModel.pMaterials[i].texureId = i;
	//}
	/* End 3DS Model */

	/* Begin Regular Model */
	glGenTextures(2, textures);

	// Load the body texture
	glBindTexture(GL_TEXTURE_2D, textures[BODY_TEXTURE]);
	pBytes = gltLoadTGA("Textures/body.tga", &iWidth, &iHeight, &iComponents, &eFormat);
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
	pBytes = gltLoadTGA("Textures/glass.tga", &iWidth, &iHeight, &iComponents, &eFormat);
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
	/* End Regular Model */

	// initialize transform
	Reset(initPosition);
	translationAcc = { 0.0002/2, 0.0002/2, 0.0005/2 };
	rotationAcc = { 0.0015, 0.0015, 0.0015 };
	savePoint = initPosition;
	PlayerController::PlayerLocation = &position;

	collider.SetCollider(position, 0.05f, this, Tag::TShip);
	CollisionSystem::AddCollider(&collider);
}

SpaceShip::~SpaceShip()
{
}


void SpaceShip::Reset(Vector3 position)
{
	this->position = position;
	forward = unitZ;
	up = unitY;
	right = unitX;
	translationSpeed = zero;
	rotationSpeed = zero;
	pose = zero;
}

void SpaceShip::DrawSpaceShip()
{
	//glTranslatef(model_pos.x, model_pos.y, model_pos.z);
	//gluLookAt(model_pos.x, model_pos.y, model_pos.z,
	//	model_pos.x + forward.x, model_pos.y + forward.y, model_pos.z + forward.z,
	//	up.x, up.y, up.z);
	glPushMatrix();
	{
		glTranslatef(0, -0.01/2, -0.04/2);
		glRotatef(180, 0, 1, 0);
		glRotatef(pose.z, 0, 0, 1);
		glRotatef(-pose.y, 0, 1, 0);
		glRotatef(pose.x, 1, 0, 0);
		//glRotatef(-asin(forward.y) * 180 / PI, 1, 0, 0);
		//glRotatef(asin(forward.x / sqrt(forward.x * forward.x + forward.z * forward.z)) * 180 / PI, 0, 1, 0);
		glPushMatrix();
		{
			//gluLookAt(0, 0, 0, 0, 0, 1, 0, 1, 0);
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			glBindTexture(GL_TEXTURE_2D, textures[BODY_TEXTURE]);
			glScalef(.0002/2, .0002/2, .0002/2);
			glCallList(bodyList); //DrawBody();
		}
		glPopMatrix();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(0.0f, 0.00132f/2, 0.00555f/2);
		glBindTexture(GL_TEXTURE_2D, textures[GLASS_TEXTURE]);

		glScalef(0.0002/2, 0.0002/2, 0.0002/2);
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

	// update pose
	pose.x += SetZero(controller.Rotation.x - 1, -Sign(pose.x) / 4.0, controller.Rotation.x - 1);
	pose.y += SetZero(controller.Rotation.y - 1, -Sign(pose.y) / 4.0, controller.Rotation.y - 1);
	pose.z += SetZero(controller.Rotation.z - 1, -Sign(pose.z) / 4.0, controller.Rotation.z - 1);
	pose.x = Clip(pose.x, -pose_limit.x, pose_limit.x);
	pose.y = Clip(pose.y, -pose_limit.y, pose_limit.y);
	pose.z = Clip(pose.z, -pose_limit.z, pose_limit.z);

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
	//rotationSpeed.x = RoundZero(rotationSpeed.x, RoundThreshold);
	//rotationSpeed.y = RoundZero(rotationSpeed.y, RoundThreshold);
	//rotationSpeed.z = RoundZero(rotationSpeed.z, RoundThreshold);
	//if (translationSpeed.Norm() < RoundThreshold) {
	//	translationSpeed = zero;
	//}

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
	Vector3 tmpPos = position;
	// warp
	position = position.EltWiseAdd(translationSpeed);
	if (position.Norm() > Galaxy::BoudningSphereRadius) {
		position = tmpPos.SclMul(-1).EltWiseAdd(translationSpeed);
	}

	// check collsion
	SphereCollider* other = collider.Update(position.EltWiseAdd(forward.SclMul(0.4f)).EltWiseAdd(up.SclMul(0.1f)));
	if (other != NULL) {
		if (other->tag == Tag::TStar) {
			OnCollision();
			GameController::OnDeath();
		}
		if (other->tag == Tag::TTrack) {
			Track *track = (Track*)(other->parent);
			savePoint = track->SavePoint();
			track->Update();
			GameController::TrackPassed();
		}
	}
}

void SpaceShip::OnCollision()
{
	Reset(savePoint);
}
