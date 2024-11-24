#include "raylib.h"
#include "intro.h"
#include "font.h"
#include "level_end.h"
#include "levels.h"

enum Screen
{
	after_intro,
	menu,
	options,
	help,
	levels
};

int main()
{
	SetConfigFlags(FLAG_FULLSCREEN_MODE);
	InitWindow(0, 0, "Parolino");
	ChangeDirectory("resources"); // to not prefix every resource with "resources/"

	// Codepoints are null and codepointCount - 0 so the font applies to default characters
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
	while (!WindowShouldClose()) // Run the loop until the user presses ESCAPE or the Quit button in the menu
	{
		switch (currentScreen)
		{
			// Fade in after intro plays
			case after_intro:
			{
				frame++;
				alpha += 0.1f;

				if (frame >= 70)
				{
					currentScreen = menu;
					frame = 0.0f;
				}
			}

			case menu:
			{
				BeginDrawing();
					ClearBackground(Color{217, 255, 224, 255});
					DrawTextEx(title_font, "Parolino", title_position, title_size, title_spacing, Fade(BLACK, alpha));
					DrawTextEx(text_font, "Play", play_button_position, text_size, text_spacing, Fade(BLACK, alpha));
				EndDrawing();
				break;
			}

			case options:

				break;

			case levels:
			{
				switch (playLevel(level))
				{
					case win: level++; break;
					case win_and_exit_to_menu: level++;
					case invalid_level:
					case exit_to_menu: currentScreen = menu; break;
				}
			}
		}
	}

	UnloadFont(title_font);
	UnloadFont(text_font);
	// Destroy the window and clean up the OpenGL context
	CloseWindow();
}