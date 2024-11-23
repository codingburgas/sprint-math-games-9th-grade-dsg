#include "raylib.h"
#include "intro.h"
#include "font.h"

enum Screen
{
	after_intro,
	menu,
	options,
	help,
	level
};

int main()
{
	SetConfigFlags(FLAG_FULLSCREEN_MODE);
	InitWindow(0, 0, "Parolino");
	ChangeDirectory("resources"); // to not prefix every resource with "resources/"

	// Codepoints are set to nullptr, and codepointCount is set to 0, just so the font is applied to default characters
	const Font title_font = LoadFontEx("bBreakPassword.ttf", title_size, nullptr, 0);
	const Font text_font = LoadFontEx("bBreakPassword.ttf", text_size, nullptr, 0);
	const Vector2 title_position = Vector2{(GetScreenWidth() - MeasureTextEx(title_font, "Parolino", title_size, title_spacing).x) / 2, 220.0f};
	const Vector2 play_button_position = Vector2{(GetScreenWidth() - MeasureTextEx(text_font, "Play", text_size, text_spacing).x) / 2, 600.0f};

	Screen currentScreen = after_intro;
	int level = 0;

	int frame = 0;
	float alpha = 0.0f;

	SetTargetFPS(60);

	playIntro();
	// Game loop
	while (!WindowShouldClose()) // Run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// Update variables
		switch (currentScreen)
		{
			// Fade in after intro plays
			case after_intro:
				frame++;
				alpha += 0.1f;
				if (frame >= 70)
				{
					currentScreen = menu;
				}
				break;

			case menu:
				
				break;

			case options:

				break;
		}

		// Draw the UI
		BeginDrawing();
			switch (currentScreen)
			{
				case after_intro:
				case menu:
					ClearBackground(Color{217, 255, 224, 255});
					DrawTextEx(title_font, "Parolino", title_position, title_size, title_spacing, Fade(BLACK, alpha));
					DrawTextEx(text_font, "Play", play_button_position, text_size, text_spacing, Fade(BLACK, alpha));
					break;

				case options:

					break;
			}
		EndDrawing();
	}

	// Destroy the window and clean up the OpenGL context
	CloseWindow();
}