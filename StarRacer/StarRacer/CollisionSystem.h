#pragma once
#include <vector>
#include "Utils.h"

class SphereCollider;

enum Tag { TShip, TStar, TTrack };

class SphereCollider {
private:
	Vector3 position;
	float radius;
public:
	void *parent;
	Tag tag;
	SphereCollider() {};
	SphereCollider(float x, float y, float z, float r, void* parent);
	SphereCollider(Vector3 position, float r, void* parent, Tag tag);
	void SetCollider(Vector3 position, float r);
	void SetCollider(Vector3 position, float r, void* parent, Tag tag);
	SphereCollider* Update(float x, float y, float z);
	SphereCollider* Update(Vector3 position);
	bool Detect(SphereCollider *other);
};

static class CollisionSystem
{
private:
	static vector<SphereCollider*> colliders;
public:
	CollisionSystem();
	~CollisionSystem();
	static void AddCollider(SphereCollider *collider);
	static void RemoveCollider(SphereCollider *collider);
	static SphereCollider* CheckCollision(SphereCollider *collider);
};
