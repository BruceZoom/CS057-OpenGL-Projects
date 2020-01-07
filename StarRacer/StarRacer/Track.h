#pragma once

#include "Utils.h"
#include "CollisionSystem.h"

class Track
{
private:
	Vector3 currentPosition;
	Vector3 lastPosition;
	float radius;
	SphereCollider collider;
	float randomRadius;
	float distance;
public:
	Track(Vector3 initPosition, float radius, float randomRadius, float distance);
	~Track();
	void Update();
	void DrawTrack();
	Vector3 SavePoint() { return currentPosition; };
};

