#include "raylib.h"
#include "intro.h"
#include "levels.h"

enum Screen
{
	after_intro,
	menu,
	levels
};

int main()
{
	SetConfigFlags(FLAG_FULLSCREEN_MODE);
	InitWindow(0, 0, "Parolino");
	ChangeDirectory("resources"); // to not prefix every resource with "resources/"

	// Create text label variables
	constexpr float title_size    = 160.0f;
	constexpr float title_spacing = 50.0f;
	constexpr float text_size     = 100.0f;
	constexpr float text_spacing  = 30.5f;
	// Codepoints are null and codepointCount - 0 thus the font applies to default characters
	const Font title_font = LoadFontEx("bBreakPassword.ttf", title_size, nullptr, 0);
	const Font text_font  = LoadFontEx("bBreakPassword.ttf", text_size,  nullptr, 0);
	const Vector2 title_position = Vector2{(GetScreenWidth() - MeasureTextEx(title_font, "Parolino", title_size, title_spacing).x) / 2, 220.0f};
	const Vector2 play_position  = Vector2{(GetScreenWidth() - MeasureTextEx(text_font, "Play", text_size, text_spacing).x) / 2, 550.0f};
	const Vector2 quit_position  = Vector2{(GetScreenWidth() - MeasureTextEx(text_font, "Quit", text_size, text_spacing).x) / 2, 780.0f};

	// Create button border variables
	constexpr float button_x_padding = 110.0f;
	constexpr float button_y_padding = 50.0f;
	constexpr Vector2 button_border_size = Vector2{390.0f + button_x_padding, 100.0f + button_y_padding};
	const Vector2 play_border_position = Vector2{GetScreenWidth() / 2 - button_border_size.x / 2, play_position.y - button_y_padding / 2};
	const Vector2 quit_border_position = Vector2{GetScreenWidth() / 2 - button_border_size.x / 2, quit_position.y - button_y_padding / 2};

	// Change on button hover
	Color playColor = BLACK;
	Color quitColor = BLACK;

	Screen currentScreen = after_intro;
	int level = 1;

	float alpha = 0.0f;

	SetExitKey(KEY_NULL); // Remove default
	bool shouldQuit = false;

	SetTargetFPS(60);

	playIntro();
	// Game loop
	while (!WindowShouldClose() && !shouldQuit) // Run the loop until the user presses the Quit button in the menu
	{
		switch (currentScreen)
		{
			// Fade in after intro plays
			case after_intro:
			{
				alpha += 0.1f;

				if (alpha >= 1.0f)
				{
					alpha = 1.0f;
					currentScreen = menu;
				}

				BeginDrawing();
					ClearBackground(Color{217, 255, 224, 255});
					DrawTextEx(title_font, "Parolino", title_position, title_size, title_spacing, Fade(BLACK, alpha));
					DrawTextEx(text_font, "Play", play_position, text_size, text_spacing, Fade(BLACK, alpha));
					DrawRectangleRoundedLinesEx(
						Rectangle{play_border_position.x, play_border_position.y, button_border_size.x, button_border_size.y},
						0.1f,
						0,
						3.0f,
						Fade(BLACK, alpha)
					);
					DrawTextEx(text_font, "Quit", quit_position, text_size, text_spacing, Fade(BLACK, alpha));
					DrawRectangleRoundedLinesEx(
						Rectangle{quit_border_position.x, quit_border_position.y, button_border_size.x, button_border_size.y},
						0.1f,
						0,
						3.0f,
						Fade(BLACK, alpha)
					);
				EndDrawing();
				break;
			}

			case menu:
			{
				if (CheckCollisionPointRec(GetMousePosition(), Rectangle{play_border_position.x, play_border_position.y, button_border_size.x, button_border_size.y}))
				{
					playColor = DARKGREEN;
					if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
					{
						currentScreen = levels;
					}
				}
				else
				{
					playColor = BLACK;
				}

				if (CheckCollisionPointRec(GetMousePosition(), Rectangle{quit_border_position.x, quit_border_position.y, button_border_size.x, button_border_size.y}))
				{
					quitColor = MAROON;
					if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
					{
						shouldQuit = true;
					}
				}
				else
				{
					quitColor = BLACK;
				}

				BeginDrawing();
					ClearBackground(Color{217, 255, 224, 255});
					DrawTextEx(title_font, "Parolino", title_position, title_size, title_spacing, BLACK);
					DrawTextEx(text_font, "Play", play_position, text_size, text_spacing, playColor);
					DrawRectangleRoundedLinesEx(
						Rectangle{play_border_position.x, play_border_position.y, button_border_size.x, button_border_size.y},
						0.1f,
						0,
						3.0f,
						playColor
					);
					DrawTextEx(text_font, "Quit", quit_position, text_size, text_spacing, quitColor);
					DrawRectangleRoundedLinesEx(
						Rectangle{quit_border_position.x, quit_border_position.y, button_border_size.x, button_border_size.y},
						0.1f,
						0,
						3.0f,
						quitColor
					);
				EndDrawing();
				break;
			}

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

	// Unload resources so they can be cleaned up
	UnloadFont(title_font);
	UnloadFont(text_font);
	// Destroy the window and clean up the OpenGL context
	CloseWindow();
}