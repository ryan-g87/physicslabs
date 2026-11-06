
#include "PhysicsSimulation.h"
#include "Sphere.h"

#include <stdexcept>

// Default constructor: creates a physics simulation with no gravity.
PhysicsSimulation::PhysicsSimulation() {
	deltaTime = 0;
	time = 0;
	gravity = Vector2{ 0, 0 }; // Initializes gravity to zero.
}

// Constructor that allows gravity to be specified when creating the world.
PhysicsSimulation::PhysicsSimulation(Vector2 gravity) {
	deltaTime = 0;
	time = 0;
	this->gravity = gravity; // Stores the supplied gravity vector.
}

// Destructor: deletes all physics bodies owned by the simulation.
PhysicsSimulation::~PhysicsSimulation()
{
	for (PhysicsBody* object : objects) {
		delete object; // Frees the memory allocated for each body.
	}
	objects.clear(); // Removes all pointers from the vector.
}

// Returns the time elapsed during the most recent physics update.
float PhysicsSimulation::GetDeltaTime() const {
	return deltaTime;
}

// Returns the total elapsed simulation time.
float PhysicsSimulation::GetTime() const {
	return time;
}

// Returns the current gravity vector.
Vector2 PhysicsSimulation::GetGravity() const {
	return gravity;
}

// Returns the physics body stored at the specified index.
// Throws an exception if the index is out of range.
PhysicsBody* PhysicsSimulation::GetBody(int index) const
{
	return objects.at(index);
}

// Changes the gravity applied by the simulation.
void PhysicsSimulation::SetGravity(Vector2 direction) {
	gravity = direction;
}

// Adds a physics body to the simulation's list of objects.
void PhysicsSimulation::AddBody(PhysicsBody* body)
{
	objects.push_back(body);
}

// Updates the physics simulation using the elapsed frame time.
void PhysicsSimulation::Update(float delta)
{
	deltaTime = delta; // Store the time elapsed since the previous frame.
	time += delta;     // Add the elapsed time to the simulation clock.

	// Loop through the physics bodies in reverse order.
	for (int i = objects.size() - 1; i >= 0; --i) {
		PhysicsBody* body = objects.at(i); // Get the current body.

		// Kinematic bodies are not automatically moved by this update.
		if (!body->GetKinematic()) {
			// Retrieve the body's current velocity.
			Vector2 velocity = body->GetVelocity();

			// Apply gravity to the horizontal and vertical velocity.
			velocity.x += gravity.x * deltaTime;
			velocity.y += gravity.y * deltaTime;

			// Save the updated velocity back to the body.
			body->SetVelocity(velocity);

			// Retrieve the body's current position.
			Vector2 position = body->GetPosition();

			// Update position using velocity and time
			position.x += velocity.x * deltaTime;
			position.y += velocity.y * deltaTime;

			// Save the updated position back to the body.
			body->SetPosition(position);

			// Check whether the body has fallen beyond the cleanup boundary. and delete if it has 
			if (position.y > GetScreenHeight() + 10 || position.x < -10 || position.x > GetScreenWidth() + 10) {
				delete body;

				objects.erase(objects.begin() + i);

				continue;
			}
		}
	}
}

// Draws the physics bodies and highlights bodies that are colliding.
void PhysicsSimulation::Draw()
{
	// Loop through every body in the simulation.
	for (PhysicsBody* body : objects) {
		Color c = BLACK; // Use black unless a collision is detected.

		// Compare the current body with every other body.
		for (int j = objects.size() - 1; j >= 0; --j) {
			PhysicsBody* other = objects.at(j);

			if (body == other) continue; // Do not check a body against itself.

			// Check whether the two bodies overlap.
			if (body->CollidesWith(other)) {
				c = RED; // Highlight the body in red if they collide.
			}
		}

		body->Draw(c);
	}
}