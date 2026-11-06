#include <cmath>
#include <raylib.h>

struct object {
	Vector2 position;
	float freq, amp;
};

object firstObject;

void update();

int main(int argc, char** argv) {
	InitWindow(800, 450, "Game Physics - Ryan Goodman <insert student id>");

	firstObject.position.x = 400;
	firstObject.position.y = 225;
	firstObject.freq = 3;
	firstObject.amp = 30;

	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(RAYWHITE);
			update();
			DrawText("Ryan Goodman", 20, 410, 20, BLACK);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}

void update() {
	double totalT = GetTime();
	float deltaT = GetFrameTime();

	// Update the object position
	double theta = totalT * firstObject.freq;
	double shift = firstObject.amp * firstObject.freq * deltaT;
	firstObject.position.y += cos(theta) * shift;
	firstObject.position.x += -sin(theta) * shift;

	// Render the object
	DrawCircle(firstObject.position.x, firstObject.position.y, 10, GREEN);
}