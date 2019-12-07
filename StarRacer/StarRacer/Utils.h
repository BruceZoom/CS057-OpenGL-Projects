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

typedef struct {
	Vector3 position;
	float radius = 0;
	Vector3 axis = {0, 1, 0};
	float rotateDegree = 0;
} BallTransform;

typedef struct {
	BallTransform transform;
	float rotateSpeed;
} Star;

#pragma endregion


#pragma region Drawer

void DrawSphere(float X, float Y, float Z, float Radius, int Slices = 30, int Stacks = 50);

#pragma endregion
