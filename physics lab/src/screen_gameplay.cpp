/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/
#ifndef RAYGUI_IMPLEMENTATION
	#define RAYGUI_IMPLEMENTATION
#endif
#include "raylib.h"
#include "raygui.h"
#include "screens.h"

#include <cmath>

#include "PhysicsSimulation.h"
#include "Plane.h"
#include "Sphere.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

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


//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;

	cannon.launchAngle = 45;
	cannon.launchPosition.x = 20;
	cannon.launchPosition.y = 700;
	cannon.launchSpeed = 50;

	CollisionSphere->SetPosition(sphereLocation);

	world.AddBody(CollisionSphere);
	world.AddBody(CollisionPlane);
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
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

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
	double totalT = GetTime();
	float deltaT = GetFrameTime();

	world.Update(deltaT);

	// +90 to account for 0 degrees being straight down
	float theta = (cannon.launchAngle + 90) * DEG2RAD;
	float opp = sin(theta);
	float adj = cos(theta);

	if (IsKeyReleased(KEY_SPACE)) {
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

	DrawText("Ryan Goodman", 20, 738, 20, BLACK);
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}