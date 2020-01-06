#include "CollisionSystem.h"


vector<SphereCollider*> CollisionSystem::colliders = {};

CollisionSystem::CollisionSystem()
{
}


CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::AddCollider(SphereCollider *collider)
{
	if (collider == NULL) return;
	for (int i = 0; i < colliders.size(); i++) {
		if (colliders[i] == collider) return;
	}
	colliders.push_back(collider);
}

void CollisionSystem::RemoveCollider(SphereCollider * collider)
{
	if (collider == NULL) return;
	for (int i = colliders.size()-1; i >= 0; i--) {
		if (colliders[i] == collider) colliders.erase(colliders.begin() + i);
	}
}

SphereCollider * CollisionSystem::CheckCollision(SphereCollider * collider)
{
	for (int i = 0; i < colliders.size(); i++) {
		if (colliders[i]->Detect(collider)) return colliders[i];
	}
	return nullptr;
}

SphereCollider::SphereCollider(float x, float y, float z, float r, void * parent)
{
	position = { x, y, z };
	radius = r;
	this->parent = parent;
}

SphereCollider::SphereCollider(Vector3 position, float r, void * parent, Tag tag)
{
	this->position = position;
	radius = r;
	this->parent = parent;
	this->tag = tag;
}

void SphereCollider::SetCollider(Vector3 position, float r)
{
	this->position = position;
	this->radius = r;
}

void SphereCollider::SetCollider(Vector3 position, float r, void * parent, Tag tag)
{
	this->position = position;
	this->radius = r;
	this->parent = parent;
	this->tag = tag;
}

SphereCollider* SphereCollider::Update(float x, float y, float z)
{
	this->position = { x, y, z };
	// detect collision
	return CollisionSystem::CheckCollision(this);
}

SphereCollider* SphereCollider::Update(Vector3 position)
{
	this->position = position;
	// detect collision
	return CollisionSystem::CheckCollision(this);
}

bool SphereCollider::Detect(SphereCollider * other)
{
	if (other == this) return false;
	return (position.EltWiseAdd(other->position.SclMul(-1)).Norm() <= radius + other->radius);
}
