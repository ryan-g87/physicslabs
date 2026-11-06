#pragma once

#include "PhysicsBody.h"

/// <summary>
/// Sphere Physics Body
/// </summary>
class Sphere : public PhysicsBody
{
public:
	/// <summary>
	/// Construct Dynamic Sphere
	/// </summary>
	/// <param name="radius">Radius of the sphere</param>
	Sphere(float radius);

	/// <summary>
	/// Construct Physics Sphere
	/// </summary>
	/// <param name="radius">Radius of the sphere</param>
	/// <param name="isKinematic">Whether the physics body is kinematic</param>
	Sphere(float radius, bool isKinematic);

	/// <summary>
	/// Get the Radius of the sphere
	/// </summary>
	/// <returns>Radius</returns>
	float GetRadius() const;

	/// <summary>
	/// Set the Radius
	/// </summary>
	/// <param name="radius">Radius of the sphere</param>
	void SetRadius(float radius);

	/// <summary>
	/// Check for collision with another physics body
	/// </summary>
	/// <param name="other">Physics body to check for collisions with</param>
	/// <returns>Collision state</returns>
	virtual bool CollidesWith(PhysicsBody* other) override;

	/// <summary>
	/// Draw the Sphere
	/// </summary>
	/// <param name="color">Color to draw the sphere with</param>
	virtual void Draw(Color color) override;

private:
	float radius;
};

