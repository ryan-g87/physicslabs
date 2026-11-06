#include "Plane.h"
#include "Sphere.h"

#include <raymath.h>
#include <stdexcept>

Plane::Plane(Vector2 point, Vector2 normal) : PhysicsBody(Body_Type::PLANE, true), isHalfSpace(false) {
	position = point;
	this->normal = Vector2Normalize(normal);
}
Plane::Plane(Vector2 point, Vector2 normal, bool isHalfSpace) : PhysicsBody(Body_Type::PLANE, true), isHalfSpace(isHalfSpace) {
	position = point;
	this->normal = Vector2Normalize(normal);
}

Vector2 Plane::GetNormal() const {
	return normal;
}

bool Plane::GetHalfSpace() const {
	return isHalfSpace;
}

void Plane::SetNormal(Vector2 value) {
	normal = Vector2Normalize(value);
}

void Plane::SetHalfSpace(bool value) {
	isHalfSpace = value;
}

bool Plane::CollidesWith(PhysicsBody* other) {
	switch (other->GetType())
	{
	case Body_Type::SPHERE:
	{
		Sphere* otherSphere = (Sphere*)other;
		float closeDistance = Vector2DotProduct(normal, other->GetPosition() - position) - otherSphere->GetRadius();
		if (isHalfSpace) return closeDistance <= 0;

		float farDistance = closeDistance + otherSphere->GetRadius() * 2;

		return closeDistance <= 0 && farDistance >= 0;
	}
	case Body_Type::PLANE:
		return abs(Vector2DotProduct(normal, ((Plane*)other)->normal)) != 1;

	default:
		throw std::invalid_argument("Unknown physics type");
	}
}

void Plane::Draw(Color color) {
	Vector2 slope{ -normal.y * 10000, normal.x * 10000 };

	DrawLineEx(Vector2Subtract(position, slope), Vector2Add(position, slope), 5, color);

	if (isHalfSpace) {
		Vector2 boxPosition = Vector2Subtract(position, Vector2Scale(normal, 10000));
		DrawLineEx(Vector2Subtract(boxPosition, slope), Vector2Add(boxPosition, slope), 20000, ColorAlpha(color, 0.3f));
	}

	Vector2 normalPoint = Vector2Scale(normal, 20);
	DrawLine(position.x, position.y, position.x + normalPoint.x, position.y + normalPoint.y, color);
}