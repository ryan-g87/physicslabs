#include "Sphere.h"
#include <raymath.h>
#include <stdexcept>

//crate and space thats is kitmatic and own that is not 
Sphere::Sphere(float radius) : PhysicsBody(Body_Type::SPHERE, false), radius(radius) {}
Sphere::Sphere(float radius, bool isKinematic) : PhysicsBody(Body_Type::SPHERE, isKinematic), radius(radius) {}

float Sphere::GetRadius() const {
	return radius;
}

void Sphere::SetRadius(float radius) {
	this->radius = radius;
}
//chek if it coldies with a other speach 

bool Sphere::CollidesWith(PhysicsBody* other) {
	switch (other->GetType())
	{
	case Body_Type::SPHERE:
	{
		float xDistance = other->GetPosition().x - position.x;
		float yDistance = other->GetPosition().y - position.y;
		float totalDistance = sqrt(xDistance * xDistance + yDistance * yDistance);

		return totalDistance < ((Sphere*)other)->GetRadius() + radius;
	}

	case Body_Type::PLANE:
		return other->CollidesWith(this);

	default:
		throw std::invalid_argument("Unknown physics type");
	}
}

void Sphere::Draw(Color color) {
	DrawCircle(position.x, position.y, radius, color);
}