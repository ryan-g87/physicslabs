#pragma once
#include <raylib.h>

/// <summary>
/// Enumeration for type of Physics body
/// </summary>
enum class Body_Type {
	SPHERE,
	PLANE
};

/// <summary>
/// Abstract Physics Body
/// </summary>
class PhysicsBody
{
public:
	/// <summary>
	/// Base constructor
	/// </summary>
	/// <param name="type">Body_Type of the physics body</param>
	/// <param name="isKinematic">Whether the body is effected by the physics system</param>
	PhysicsBody(Body_Type type, bool isKinematic);

	/// <summary>
	/// Returns the position of the physics body
	/// </summary>
	/// <returns>Vector2 position</returns>
	Vector2 GetPosition() const;

	/// <summary>
	/// Returns the velocity of the physics body
	/// </summary>
	/// <returns>Vector2 velocity</returns>
	Vector2 GetVelocity() const;

	/// <summary>
	/// Returns the drag experienced by the physics body
	/// </summary>
	/// <returns>Float drag</returns>
	float GetDrag() const;

	/// <summary>
	/// Returns the mass of the physics body
	/// </summary>
	/// <returns>Float mass</returns>
	float GetMass() const;

	/// <summary>
	/// Returns the type of the physics body
	/// </summary>
	/// <returns>Body_Type type</returns>
	Body_Type GetType() const;

	/// <summary>
	/// Returns the kinematic value
	/// </summary>
	/// <returns>Boolean isKinematic</returns>
	bool GetKinematic() const;

	/// <summary>
	/// Sets the position of the physics body
	/// </summary>
	/// <param name="value">Vector2 position</param>
	void SetPosition(Vector2 value);

	/// <summary>
	/// Sets the velocity of the physics body
	/// </summary>
	/// <param name="value">Vector2 velocity</param>
	void SetVelocity(Vector2 value);

	/// <summary>
	/// Set the drag of the physics body
	/// </summary>
	/// <param name="value">Float drag</param>
	void SetDrag(float value);

	/// <summary>
	/// Set the mass of the physics body
	/// </summary>
	/// <param name="value">Float mass</param>
	void SetMass(float value);

	/// <summary>
	/// Set whether the physics body is kinematic
	/// </summary>
	/// <param name="value">True if the body shouldn't move</param>
	void SetKinematic(bool value);


	/// <summary>
	/// Check for collision with another physics body
	/// </summary>
	/// <param name="other">Physics body to check for collisions with</param>
	/// <returns>Collision state</returns>
	virtual bool CollidesWith(PhysicsBody* other) = 0;
	/// <summary>
	/// Draw the Sphere
	/// </summary>
	/// <param name="color">Color to draw the sphere with</param>
	virtual void Draw(Color color) = 0;
protected:
	Body_Type type;
	Vector2 position, velocity;
	float drag, mass;

	bool isKinematic;
};

