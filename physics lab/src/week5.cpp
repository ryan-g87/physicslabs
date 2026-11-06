#include <cmath>
#include <raylib.h>
#include <string>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "PhysicsSimulation.h"
#include "Sphere.h"

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
Vector2 gravity{ 0, 98.1f };
Vector2 sphereLocation{ 500, 500 };
PhysicsSimulation world(gravity);
Sphere *CollisionSphere = new Sphere(100, true);

void drawGUI();
void update();

int main(int argc, char** argv) {
	InitWindow(1024, 768, "Game Physics - Ryan Goodman <insert student id>");
	SetTargetFPS(60);

	cannon.launchAngle = 45;
	cannon.launchPosition.x = 20;
	cannon.launchPosition.y = 700;
	cannon.launchSpeed = 50;

	CollisionSphere->SetPosition(sphereLocation);

	world.AddBody(CollisionSphere);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		update();
		drawGUI();
		DrawText("Ryan Goodman", 20, 738, 20, BLACK);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}

void drawGUI() {
	GuiPanel(Rectangle{ 20, 20, 300, 140 }, "Controls");
	GuiLabel(Rectangle{ 25, 50, 100, 20 }, "Launch Position: ");
	GuiLabel(Rectangle{ 25, 70, 100, 20 }, "Launch Angle: ");
	GuiLabel(Rectangle{ 25, 90, 100, 20 }, "Launch Speed: ");
	GuiLabel(Rectangle{ 25, 110, 100, 20 }, "Gravity Strength: ");
	GuiLabel(Rectangle{ 25, 130, 100, 20 }, "Collision Sphere: ");
	GuiSlider(Rectangle{ 125, 50, 50, 20 }, "", "", &cannon.launchPosition.x, 20, 1004);
	GuiSlider(Rectangle{ 175, 50, 50, 20 }, "", "", &cannon.launchPosition.y, 20, 748);
	GuiSlider(Rectangle{ 125, 70, 100, 20 }, "", "", &cannon.launchAngle, 0, 360);
	GuiSlider(Rectangle{ 125, 90, 100, 20 }, "", "", &cannon.launchSpeed, 60, 400);
	GuiSlider(Rectangle{ 125, 110, 50, 20 }, "", "", &gravity.x, -200, 200);
	GuiSlider(Rectangle{ 175, 110, 50, 20 }, "", "", &gravity.y, -200, 200);
	GuiSlider(Rectangle{ 125, 130, 50, 20 }, "", "", &sphereLocation.x, 20, 1004);
	GuiSlider(Rectangle{ 175, 130, 50, 20 }, "", "", &sphereLocation.y, 20, 748);

	char buff[20];
	sprintf(buff, "%.2f %0.2f", cannon.launchPosition.x, cannon.launchPosition.y);
	GuiLabel(Rectangle{ 235, 50, 100, 20 }, buff);

	sprintf(buff, "%.2f", cannon.launchAngle);
	GuiLabel(Rectangle{ 235, 70, 100, 20 }, buff);
	sprintf(buff, "%.2f", cannon.launchSpeed);
	GuiLabel(Rectangle{ 235, 90, 100, 20 }, buff);

	sprintf(buff, "%.2f %0.2f", gravity.x, gravity.y);
	GuiLabel(Rectangle{ 235, 110, 100, 20 }, buff);

	sprintf(buff, "%.2f %0.2f", sphereLocation.x, sphereLocation.y);
	GuiLabel(Rectangle{ 235, 130, 100, 20 }, buff);

	cannon.launchAngle = ((int)cannon.launchAngle / 5) * 5; // lock the launch angle to the closest 5
	CollisionSphere->SetPosition(sphereLocation);
	world.SetGravity(gravity);
}

void update() {
	double totalT = GetTime();
	float deltaT = GetFrameTime();

	world.Update(deltaT);

	// +90 to account for 0 degrees being straight down
	float theta = (cannon.launchAngle + 90) * DEG2RAD;
	float opp = sin(theta);
	float adj = cos(theta);

	if (IsKeyReleased(VK_SPACE)) {
		PhysicsBody* body = new Sphere(20);

		body->SetMass(DEFAULT_MASS);
		body->SetDrag(DEFAULT_DRAG);

		body->SetPosition(cannon.launchPosition);
		body->SetVelocity(Vector2{ opp * cannon.launchSpeed, adj * cannon.launchSpeed });

		world.AddBody(body);
	}

	// Render the object
	DrawCircle(cannon.launchPosition.x, cannon.launchPosition.y, 20, RED);
	DrawLine(cannon.launchPosition.x, cannon.launchPosition.y, cannon.launchPosition.x + opp * 1000, cannon.launchPosition.y + adj * 1000, RED);

	world.Draw();
}