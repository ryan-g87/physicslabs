#pragma once

#include "PhysicsBody.h"

/// <summary>
/// Plane Physics body
/// </summary>
class Plane : public PhysicsBody
{
public:
	/// <summary>
	/// Constructs a Plane 
	/// </summary>
	/// <param name="point">Position of the plane</param>
	/// <param name="normal">Normal of the plane</param>
	Plane(Vector2 point, Vector2 normal);

	/// <summary>
	/// Constructs a Plane or Halfspace
	/// </summary>
	/// <param name="point">Position of the plane</param>
	/// <param name="normal">Normal of the plane</param>
	/// <param name="isHalfSpace">Whether we are representing a plane or halfspace</param>
	Plane(Vector2 point, Vector2 normal, bool isHalfSpace);

	/// <summary>
	/// Get the normal of the plane
	/// </summary>
	/// <returns>Vector2 normal</returns>
	Vector2 GetNormal() const;

	/// <summary>
	/// Get Halfspace value
	/// </summary>
	/// <returns>True if the physicsbody is a halfspace</returns>
	bool GetHalfSpace() const;

	/// <summary>
	/// Set the normal of the plane
	/// </summary>
	/// <param name="value">Vector2 to change the normal to</param>
	void SetNormal(Vector2 value);

	/// <summary>
	/// Set the halfspace value of the plane
	/// </summary>
	/// <param name="value">True if Halfspace</param>
	void SetHalfSpace(bool value);

	/// <summary>
	/// Check for collision with another physics body
	/// </summary>
	/// <param name="other">Physics body to check for collisions with</param>
	/// <returns>Collision state</returns>
	virtual bool CollidesWith(PhysicsBody* other) override;

	/// <summary>
	/// Draw the Plane/Halfspace
	/// </summary>
	/// <param name="color">Color to draw the Plane/Halfspace with</param>
	virtual void Draw(Color color) override;

private:
	Vector2 normal;
	bool isHalfSpace;
};

