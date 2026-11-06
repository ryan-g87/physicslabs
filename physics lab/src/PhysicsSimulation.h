#pragma once
#include <raylib.h>
#include <vector>

#include "PhysicsBody.h"

class PhysicsSimulation
{
public:
	PhysicsSimulation();
	PhysicsSimulation(Vector2);
	~PhysicsSimulation();

	float GetDeltaTime() const;
	float GetTime() const;
	Vector2 GetGravity() const;
	PhysicsBody* GetBody(int index) const;

	void SetGravity(Vector2 direction);
	void AddBody(PhysicsBody* body);

	void Update(float delta);
	void Draw();

private:
	float deltaTime;
	float time;
	Vector2 gravity;

	std::vector<PhysicsBody*> objects;
};

