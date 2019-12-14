#pragma once
#include <math.h>   
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.1415

using namespace std;
#pragma region DataStruct

typedef struct {
	float x = 0;
	float y = 0;
	float z = 0;
} Vector3;

const Vector3 zero = { 0, 0, 0 };
const Vector3 unitX = { 1, 0, 0 };
const Vector3 unitY = { 0, 1, 0 };
const Vector3 unitZ = { 0, 0, 1 };

typedef struct {
	Vector3 position;
	float radius = 0;
} SphereTransform;

typedef struct {
	SphereTransform transform;
	Vector3 rotateAxis = { 0, 1, 0 };
	float rotateDegree = 0;
	float rotateSpeed = 0;
	Vector3 revolveCenter = {0, 0, 0};	// the revolve plane can only be the x-z plane
	float revolveDegree = 0;
	float revolveRadius = 0;
	float revolveSpeed = 0;
} Star;

#pragma endregion


#pragma region Drawer

void DrawSphere(float X, float Y, float Z, float Radius, int Slices = 30, int Stacks = 50);

#pragma endregion
