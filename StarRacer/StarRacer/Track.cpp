#include "Track.h"
#include "glut.h"
#include <cmath>

Track::Track(Vector3 initPosition, float radius, float randomRadius, float distance)
{
	currentPosition = initPosition;
	lastPosition = initPosition.EltWiseAdd({ 0, 0, -10 });
	this->radius = radius;
	this->randomRadius = randomRadius;
	this->distance = distance;

	collider.SetCollider(currentPosition, radius, this, TTrack);
	CollisionSystem::AddCollider(&collider);
}

Track::~Track()
{
}

void Track::Update()
{
	Vector3 candidate = currentPosition.EltWiseAdd(
		currentPosition.EltWiseAdd(lastPosition.SclMul(-1)).Normalize().SclMul(distance));
	SphereCollider *other;
	do
	{
		candidate = candidate.EltWiseAdd({ (float)rand() / RAND_MAX * randomRadius,
										(float)rand() / RAND_MAX * randomRadius,
										(float)rand() / RAND_MAX * randomRadius });
		other = collider.Update(candidate);
	} while (other != NULL);
	lastPosition = currentPosition;
	currentPosition = candidate;
}

void Track::DrawTrack()
{
	glTranslatef(currentPosition.x,
				 currentPosition.y,
				 currentPosition.z);
	DrawSphere(0, 0, 0, radius, 10, 20, 1);
}