#pragma once
#include <math.h>   
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.1415

using namespace std;
#pragma region DataStruct

typedef struct _V3{
	float x = 0;
	float y = 0;
	float z = 0;
	float DotProduct(struct _V3 v) const {
		return x * v.x + y * v.y + z * v.z;
	}
	struct _V3 DotProduct(struct _V3 col1, struct _V3 col2, struct _V3 col3) const {
		return { DotProduct(col1),  DotProduct(col2),  DotProduct(col3) };
	}
	struct _V3 DotProduct(struct _V3 col[3]) const {
		return { DotProduct(col[0]),  DotProduct(col[1]),  DotProduct(col[2]) };
	}
	struct _V3 EltWiseMul(struct _V3 v) const {
		return { x * v.x, y * v.y, z * v.z };
	}
	struct _V3 EltWiseAdd(struct _V3 v) const {
		return { x + v.x, y + v.y, z + v.z };
	}
	struct _V3 SclMul(float alpha) const {
		return { x * alpha, y * alpha, z * alpha };
	}
	float Norm() const {
		return sqrt(x * x + y * y + z * z);
	}
	struct _V3 Normalize() {
		return SclMul(1 / Norm());
	}
	void Print() {
		cout << x << " " << y << " " << z << endl;
	}
} Vector3;

const Vector3 zero = { 0, 0, 0 };
const Vector3 unitX = { 1, 0, 0 };
const Vector3 unitY = { 0, 1, 0 };
const Vector3 unitZ = { 0, 0, 1 };

typedef struct {
	Vector3 position;
	float radius = 0;
} SphereTransform;

#pragma endregion


#pragma region Drawer

void DrawSphere(float X, float Y, float Z, float Radius, int Slices = 30, int Stacks = 50);

#pragma endregion


#pragma region Utils

#define RoundZero(x, th) (abs(x) < (th) ? 0 : (x))
#define SetZero(x, v0, v1) ((x == 0) ? (v0) : (v1))
#define Min(x, y) ((x) < (y) ? (x) : (y))
#define Max(x, y) ((x) > (y) ? (x) : (y))
#define Clip(x, lo, hi) (Max((lo), Min((x), (hi))))
#define Sign(x) ((x) > 0 ? 1 : ((x) < 0 ? -1 : 0))

#pragma endregion

