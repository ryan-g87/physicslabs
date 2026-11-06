#include "PhysicsBody.h"
#include <limits>

PhysicsBody::PhysicsBody(Body_Type type, bool isKinematic) : type(type), drag(0), mass(0), position(Vector2{ 0,0 }), isKinematic(isKinematic) {
	mass = std::numeric_limits<float>::epsilon();
}
//retuer the varibles the phusbody need 
Vector2 PhysicsBody::GetPosition() const {
	return position;
}

Vector2 PhysicsBody::GetVelocity() const {
	return velocity;
}

float PhysicsBody::GetDrag() const {
	return drag;
}

float PhysicsBody::GetMass() const {
	return mass;
}

Body_Type PhysicsBody::GetType() const {
	return type;
}

bool PhysicsBody::GetKinematic() const {
	return isKinematic;
}
//update the viaribals
void PhysicsBody::SetPosition(Vector2 value) {
	position = value;
}

void PhysicsBody::SetVelocity(Vector2 value) {
	velocity = value;
}

void PhysicsBody::SetDrag(float value) {
	drag = value;
}

void PhysicsBody::SetMass(float value) {
	mass = value;
}

void PhysicsBody::SetKinematic(bool value) {
	isKinematic = value;
}