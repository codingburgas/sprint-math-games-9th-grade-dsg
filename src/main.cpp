#include "raylib.h"
#include "intro.h"

int main()
{
	//SetConfigFlags(FLAG_FULLSCREEN_MODE);
	InitWindow(GetScreenWidth(), GetScreenHeight(), "Parolino");
	ChangeDirectory("resources"); // for easier access to resources

	int level = 0;

	Vector2 titleSize = MeasureTextEx(GetFontDefault(), "Parolino", 160.0f, 80.0f);
	Vector2 titlePosition = Vector2{(GetScreenWidth() - titleSize.x) / 2, 220.0f};

	SetTargetFPS(60);

	playIntro();
	// Game loop
	while (!WindowShouldClose()) // Run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// Update variables
		switch (level)
		{
		case 0: // Main menu

			break;

		case 1:

			break;
		}

		BeginDrawing();
			switch (level)
			{
			case 0: // Main menu
				ClearBackground(Color{217, 255, 224, 255});
				DrawTextEx(GetFontDefault(), "Parolino", titlePosition, 160.0f, 80.0f, BLACK);
				break;

			case 1:

				break;
			}
		EndDrawing();
	}

	// Destory the window and clean up the OpenGL context
	CloseWindow();
}