#include <cmath>
#include <raylib.h>
#include <string>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "PhysicsSimulation.h"
#include "Sphere.h"
#include "Plane.h"

constexpr auto VK_SPACE = 0x20;

constexpr auto DEFAULT_MASS = 100.0f;
constexpr auto DEFAULT_DRAG = 2.5f;

struct Cannon
{
	Vector2 launchPosition;
	float launchAngle;
	float launchSpeed;
};

Cannon cannon;

// Setup Physics Simulation with variables for editing with gui
Vector2 gravity{ 0, 98.1f };
PhysicsSimulation world(gravity);

// Setup Collision Sphere with variables for editing with gui
Vector2 sphereLocation{ 500, 500 };
float sphereRadius = 100;
Sphere* CollisionSphere = new Sphere(sphereRadius, true);

// Setup Collision Plane with variables for editing with gui
Vector2 planeLocation{ 600, 600 };
float angle = 225;
bool halfSpace = true;
Plane* CollisionPlane = new Plane(planeLocation, Vector2{ cos(angle * DEG2RAD), sin(angle * DEG2RAD) }, halfSpace);

// Forward declare functions
void drawGUI();
void update();

int main(int argc, char** argv) {
	// Initialize window and setup variables
	InitWindow(1024, 768, "Game Physics - Ryan Goodman <insert student id>");
	SetTargetFPS(60);

	cannon.launchAngle = 45;
	cannon.launchPosition.x = 20;
	cannon.launchPosition.y = 700;
	cannon.launchSpeed = 350;

	CollisionSphere->SetPosition(sphereLocation);

	world.AddBody(CollisionSphere);
	world.AddBody(CollisionPlane);

	// Main Loop
	while (!WindowShouldClose()) {
		BeginDrawing();				// Start drawing
		ClearBackground(RAYWHITE);	// Begin graphics
		update();					// Call update and draw
		drawGUI();					// Draw GUI overtop
		DrawText("Ryan Goodman", 20, 738, 20, BLACK);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}

/// <summary>
/// Draws the panel that changes values
/// </summary>
void drawGUI() {
	// Panel that holds gui elemets
	GuiPanel(Rectangle{ 0, 0, 400, 200 }, "Controls");

	// Labels for various elements
	GuiLabel(Rectangle{ 5, 30, 100, 20 }, "Launch Position: ");
	GuiLabel(Rectangle{ 5, 50, 100, 20 }, "Launch Angle: ");
	GuiLabel(Rectangle{ 5, 70, 100, 20 }, "Launch Speed: ");
	GuiLabel(Rectangle{ 5, 90, 100, 20 }, "Gravity Strength: ");
	GuiLabel(Rectangle{ 5, 110, 100, 20 }, "Collision Sphere: ");
	GuiLabel(Rectangle{ 5, 130, 100, 20 }, "Plane Position: ");
	GuiLabel(Rectangle{ 5, 150, 100, 20 }, "Plane Angle: ");
	GuiLabel(Rectangle{ 5, 170, 100, 20 }, "Is Halfspace?: ");

	// Sliders to edit values
	GuiSlider(Rectangle{ 105, 30, 100, 20 }, "", "", &cannon.launchPosition.x, 20, 1004);
	GuiSlider(Rectangle{ 205, 30, 100, 20 }, "", "", &cannon.launchPosition.y, 20, 748);
	GuiSlider(Rectangle{ 105, 50, 200, 20 }, "", "", &cannon.launchAngle, 0, 360);
	GuiSlider(Rectangle{ 105, 70, 200, 20 }, "", "", &cannon.launchSpeed, 60, 400);
	GuiSlider(Rectangle{ 105, 90, 100, 20 }, "", "", &gravity.x, -200, 200);
	GuiSlider(Rectangle{ 205, 90, 100, 20 }, "", "", &gravity.y, -200, 200);
	GuiSlider(Rectangle{ 105, 110, 100, 20 }, "", "", &sphereLocation.x, 20, 1004);
	GuiSlider(Rectangle{ 205, 110, 100, 20 }, "", "", &sphereLocation.y, 20, 748);
	GuiSlider(Rectangle{ 105, 130, 100, 20 }, "", "", &planeLocation.x, 20, 1004);
	GuiSlider(Rectangle{ 205, 130, 100, 20 }, "", "", &planeLocation.y, 20, 748);
	GuiSlider(Rectangle{ 105, 150, 200, 20 }, "", "", &angle, 0, 360);

	// Lock the cannon's launch angle to nearest 5 to make aiming easier.
	cannon.launchAngle = ((int)cannon.launchAngle / 5) * 5;

	// Checkbox for true/false value
	GuiCheckBox(Rectangle{ 105, 170, 20, 20 }, "", &halfSpace);

	// Create a string buffer to hold values for printing
	char buff[20];

	// Fill buffer and print values so the user can see the results.
	sprintf(buff, "%.2f %0.2f", cannon.launchPosition.x, cannon.launchPosition.y);
	GuiLabel(Rectangle{ 315, 30, 100, 20 }, buff);

	sprintf(buff, "%.2f", cannon.launchAngle);
	GuiLabel(Rectangle{ 315, 50, 100, 20 }, buff);
	sprintf(buff, "%.2f", cannon.launchSpeed);
	GuiLabel(Rectangle{ 315, 70, 100, 20 }, buff);

	sprintf(buff, "%.2f %0.2f", gravity.x, gravity.y);
	GuiLabel(Rectangle{ 315, 90, 100, 20 }, buff);

	sprintf(buff, "%.2f %0.2f", sphereLocation.x, sphereLocation.y);
	GuiLabel(Rectangle{ 315, 110, 100, 20 }, buff);

	sprintf(buff, "%.2f %0.2f", planeLocation.x, planeLocation.y);
	GuiLabel(Rectangle{ 315, 130, 100, 20 }, buff);

	sprintf(buff, "%.2f", angle);
	GuiLabel(Rectangle{ 315, 150, 100, 20 }, buff);

	// Save updated values to the appropriate structre.
	CollisionSphere->SetPosition(sphereLocation);

	CollisionPlane->SetPosition(planeLocation);
	CollisionPlane->SetNormal(Vector2{ cos(angle * DEG2RAD), sin(angle * DEG2RAD) });
	CollisionPlane->SetHalfSpace(halfSpace);

	world.SetGravity(gravity);
}

/// <summary>
/// Performs the frame level updates
/// </summary>
void update() {
	double totalT = GetTime();
	float deltaT = GetFrameTime();

	world.Update(deltaT);

	// +90 to account for 0 degrees being straight down
	float theta = (cannon.launchAngle + 90) * DEG2RAD;
	float opp = sin(theta);
	float adj = cos(theta);

	// Check if spacebar is released to indicate firing the cannon
	if (IsKeyReleased(VK_SPACE)) {
		PhysicsBody* body = new Sphere(20);

		body->SetMass(DEFAULT_MASS);
		body->SetDrag(DEFAULT_DRAG);

		body->SetPosition(cannon.launchPosition);
		body->SetVelocity(Vector2{ opp * cannon.launchSpeed, adj * cannon.launchSpeed });

		world.AddBody(body);
	}

	// Render the cannon object and line showing the direction and arc of the cannon shot
	DrawCircle(cannon.launchPosition.x, cannon.launchPosition.y, 20, RED);
	Vector2 point = cannon.launchPosition;
	Vector2 velocity{ opp * cannon.launchSpeed, adj * cannon.launchSpeed };

	float step = GetFrameTime() / 2;
	if (step > 0)
		while (point.y < 758) {
			velocity.x += gravity.x * step;
			velocity.y += gravity.y * step;

			Vector2 position = point;
			position.x += velocity.x * step;
			position.y += velocity.y * step;

			DrawLine(point.x, point.y, position.x, position.y, RED);
			point = position;
		}

	// Draw all elements in the physics simulation
	world.Draw();
}#include <cmath>
#include <raylib.h>
#include <string>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "PhysicsSimulation.h"
#include "Sphere.h"
#include "Plane.h"

constexpr auto VK_SPACE = 0x20;

constexpr auto DEFAULT_MASS = 100.0f;
constexpr auto DEFAULT_DRAG = 2.5f;

struct Cannon
{
	Vector2 launchPosition;
	float launchAngle;
	float launchSpeed;
};

Cannon cannon;

// Setup Physics Simulation with variables for editing with gui
Vector2 gravity{ 0, 98.1f };
PhysicsSimulation world(gravity);

// Setup Collision Sphere with variables for editing with gui
Vector2 sphereLocation{ 500, 500 };
float sphereRadius = 100;
Sphere* CollisionSphere = new Sphere(sphereRadius, true);

// Setup Collision Plane with variables for editing with gui
Vector2 planeLocation{ 600, 600 };
float angle = 225;
bool halfSpace = true;
Plane* CollisionPlane = new Plane(planeLocation, Vector2{ cos(angle * DEG2RAD), sin(angle * DEG2RAD) }, halfSpace);

// Forward declare functions
void drawGUI();
void update();

int main(int argc, char** argv) {
	// Initialize window and setup variables
	InitWindow(1024, 768, "Game Physics - Ryan Goodman <insert student id>");
	SetTargetFPS(60);

	cannon.launchAngle = 45;
	cannon.launchPosition.x = 20;
	cannon.launchPosition.y = 700;
	cannon.launchSpeed = 350;

	CollisionSphere->SetPosition(sphereLocation);

	world.AddBody(CollisionSphere);
	world.AddBody(CollisionPlane);

	// Main Loop
	while (!WindowShouldClose()) {
		BeginDrawing();				// Start drawing
		ClearBackground(RAYWHITE);	// Begin graphics
		update();					// Call update and draw
		drawGUI();					// Draw GUI overtop
		DrawText("Ryan Goodman", 20, 738, 20, BLACK);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}

/// <summary>
/// Draws the panel that changes values
/// </summary>
void drawGUI() {
	// Panel that holds gui elemets
	GuiPanel(Rectangle{ 0, 0, 400, 200 }, "Controls");

	// Labels for various elements
	GuiLabel(Rectangle{ 5, 30, 100, 20 }, "Launch Position: ");
	GuiLabel(Rectangle{ 5, 50, 100, 20 }, "Launch Angle: ");
	GuiLabel(Rectangle{ 5, 70, 100, 20 }, "Launch Speed: ");
	GuiLabel(Rectangle{ 5, 90, 100, 20 }, "Gravity Strength: ");
	GuiLabel(Rectangle{ 5, 110, 100, 20 }, "Collision Sphere: ");
	GuiLabel(Rectangle{ 5, 130, 100, 20 }, "Plane Position: ");
	GuiLabel(Rectangle{ 5, 150, 100, 20 }, "Plane Angle: ");
	GuiLabel(Rectangle{ 5, 170, 100, 20 }, "Is Halfspace?: ");

	// Sliders to edit values
	GuiSlider(Rectangle{ 105, 30, 100, 20 }, "", "", &cannon.launchPosition.x, 20, 1004);
	GuiSlider(Rectangle{ 205, 30, 100, 20 }, "", "", &cannon.launchPosition.y, 20, 748);
	GuiSlider(Rectangle{ 105, 50, 200, 20 }, "", "", &cannon.launchAngle, 0, 360);
	GuiSlider(Rectangle{ 105, 70, 200, 20 }, "", "", &cannon.launchSpeed, 60, 400);
	GuiSlider(Rectangle{ 105, 90, 100, 20 }, "", "", &gravity.x, -200, 200);
	GuiSlider(Rectangle{ 205, 90, 100, 20 }, "", "", &gravity.y, -200, 200);
	GuiSlider(Rectangle{ 105, 110, 100, 20 }, "", "", &sphereLocation.x, 20, 1004);
	GuiSlider(Rectangle{ 205, 110, 100, 20 }, "", "", &sphereLocation.y, 20, 748);
	GuiSlider(Rectangle{ 105, 130, 100, 20 }, "", "", &planeLocation.x, 20, 1004);
	GuiSlider(Rectangle{ 205, 130, 100, 20 }, "", "", &planeLocation.y, 20, 748);
	GuiSlider(Rectangle{ 105, 150, 200, 20 }, "", "", &angle, 0, 360);

	// Lock the cannon's launch angle to nearest 5 to make aiming easier.
	cannon.launchAngle = ((int)cannon.launchAngle / 5) * 5;

	// Checkbox for true/false value
	GuiCheckBox(Rectangle{ 105, 170, 20, 20 }, "", &halfSpace);

	// Create a string buffer to hold values for printing
	char buff[20];

	// Fill buffer and print values so the user can see the results.
	sprintf(buff, "%.2f %0.2f", cannon.launchPosition.x, cannon.launchPosition.y);
	GuiLabel(Rectangle{ 315, 30, 100, 20 }, buff);

	sprintf(buff, "%.2f", cannon.launchAngle);
	GuiLabel(Rectangle{ 315, 50, 100, 20 }, buff);
	sprintf(buff, "%.2f", cannon.launchSpeed);
	GuiLabel(Rectangle{ 315, 70, 100, 20 }, buff);

	sprintf(buff, "%.2f %0.2f", gravity.x, gravity.y);
	GuiLabel(Rectangle{ 315, 90, 100, 20 }, buff);

	sprintf(buff, "%.2f %0.2f", sphereLocation.x, sphereLocation.y);
	GuiLabel(Rectangle{ 315, 110, 100, 20 }, buff);

	sprintf(buff, "%.2f %0.2f", planeLocation.x, planeLocation.y);
	GuiLabel(Rectangle{ 315, 130, 100, 20 }, buff);

	sprintf(buff, "%.2f", angle);
	GuiLabel(Rectangle{ 315, 150, 100, 20 }, buff);

	// Save updated values to the appropriate structre.
	CollisionSphere->SetPosition(sphereLocation);

	CollisionPlane->SetPosition(planeLocation);
	CollisionPlane->SetNormal(Vector2{ cos(angle * DEG2RAD), sin(angle * DEG2RAD) });
	CollisionPlane->SetHalfSpace(halfSpace);

	world.SetGravity(gravity);
}

/// <summary>
/// Performs the frame level updates
/// </summary>
void update() {
	double totalT = GetTime();
	float deltaT = GetFrameTime();

	world.Update(deltaT);

	// +90 to account for 0 degrees being straight down
	float theta = (cannon.launchAngle + 90) * DEG2RAD;
	float opp = sin(theta);
	float adj = cos(theta);

	// Check if spacebar is released to indicate firing the cannon
	if (IsKeyReleased(VK_SPACE)) {
		PhysicsBody* body = new Sphere(20);

		body->SetMass(DEFAULT_MASS);
		body->SetDrag(DEFAULT_DRAG);

		body->SetPosition(cannon.launchPosition);
		body->SetVelocity(Vector2{ opp * cannon.launchSpeed, adj * cannon.launchSpeed });

		world.AddBody(body);
	}

	// Render the cannon object and line showing the direction and arc of the cannon shot
	DrawCircle(cannon.launchPosition.x, cannon.launchPosition.y, 20, RED);
	Vector2 point = cannon.launchPosition;
	Vector2 velocity{ opp * cannon.launchSpeed, adj * cannon.launchSpeed };

	float step = GetFrameTime() / 2;
	if (step > 0)
		while (point.y < 758) {
			velocity.x += gravity.x * step;
			velocity.y += gravity.y * step;

			Vector2 position = point;
			position.x += velocity.x * step;
			position.y += velocity.y * step;

			DrawLine(point.x, point.y, position.x, position.y, RED);
			point = position;
		}

	// Draw all elements in the physics simulation
	world.Draw();
}