#include <cmath>
#include <raylib.h>
#include <string>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>


struct object {
	Vector2 position;
	float freq, amp;
};

struct Cannon
{
	Vector2 launchPosition;
	float launchAngle;
	float launchSpeed;
};

Cannon cannon;

void drawGUI();
void update();

int main(int argc, char** argv) {
	InitWindow(800, 450, "Game Physics - Ryan Goodman <insert student id>");
	SetTargetFPS(60);

	cannon.launchAngle = 45;
	cannon.launchPosition.x = 20;
	cannon.launchPosition.y = 390;
	cannon.launchSpeed = 50;

	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(RAYWHITE);
			drawGUI();
			update();
			DrawText("Ryan Goodman", 20, 410, 20, BLACK);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}

void drawGUI() {
	GuiPanel(Rectangle{ 20, 20, 300, 100 }, "Controls");
	GuiLabel(Rectangle{ 25, 50, 100, 20 }, "Launch Position: ");
	GuiLabel(Rectangle{ 25, 70, 100, 20 }, "Launch Angle: ");
	GuiLabel(Rectangle{ 25, 90, 100, 20 }, "Launch Speed: ");
	GuiSlider(Rectangle{ 125, 50, 50, 20 }, "", "", &cannon.launchPosition.x, 20, 800);
	GuiSlider(Rectangle{ 175, 50, 50, 20 }, "", "", &cannon.launchPosition.y, 20, 400);
	GuiSlider(Rectangle{ 125, 70, 100, 20 }, "", "", &cannon.launchAngle, 0, 360);
	GuiSlider(Rectangle{ 125, 90, 100, 20 }, "", "", &cannon.launchSpeed, 20, 400);

	char buff[20];
	sprintf(buff, "%.2f %0.2f", cannon.launchPosition.x, cannon.launchPosition.y);
	GuiLabel(Rectangle{ 235, 50, 100, 20 }, buff);

	sprintf(buff, "%.2f", cannon.launchAngle);
	GuiLabel(Rectangle{ 235, 70, 100, 20 }, buff);
	sprintf(buff, "%.2f", cannon.launchSpeed);
	GuiLabel(Rectangle{ 235, 90, 100, 20 }, buff);
}

void update() {
	double totalT = GetTime();
	float deltaT = GetFrameTime();

	// +90 to account for 0 degrees being straight down
	double theta = (cannon.launchAngle + 90) * DEG2RAD;
	float opp = 1000 * sin(theta);
	float adj = 1000* cos(theta);

	// Render the object
	DrawCircle(cannon.launchPosition.x, cannon.launchPosition.y, 20, RED);
	DrawLine(cannon.launchPosition.x, cannon.launchPosition.y, cannon.launchPosition.x + opp, cannon.launchPosition.y + adj, RED);
}