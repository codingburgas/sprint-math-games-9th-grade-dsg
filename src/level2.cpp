#include "levels.h"
#include "raylib.h"
#include <cstring>
using namespace std;

LevelEnd level2()
{
	const int center_x = GetScreenWidth() / 2;

	const Rectangle table_dimensions = Rectangle{
		0.0f,
		(float)GetScreenHeight() - 300.0f,
		(float)GetScreenWidth(),
		300.0f
	};

	const Rectangle safe_dimensions = Rectangle{
		center_x - GetScreenWidth() * 0.66f / 2,
		GetScreenHeight() - GetScreenHeight() * 0.66f - table_dimensions.height,
		GetScreenWidth() * 0.66f,
		GetScreenHeight() * 0.66f
	};
	constexpr float safe_hole_padding = 50.0f;
	const Rectangle safe_hole_dimensions = Rectangle{
		center_x - (safe_dimensions.width - 100.0f) / 2,
		safe_dimensions.y - safe_hole_padding / 2,
		safe_dimensions.width - 100.0f,
		safe_dimensions.height - 50.0f
	};
	constexpr Vector2 safe_slot_dimensions = Vector2{80.0f, 90.0f};
	constexpr int safe_slot_spacing = 25;

	constexpr float hint_size     = 40.0f;
	constexpr float hint_spacing  = 6.0f;
	constexpr float input_size    = 55.0f;
	const Font hint_font = LoadFontEx("bBreakPassword.ttf", hint_size, nullptr, 0);
	const Font input_font = LoadFontEx("bBreakPassword.ttf", input_size, nullptr, 0);

	const Vector2 hint_dimensions = MeasureTextEx(hint_font, "This person really loves fish", hint_size, hint_spacing);

	constexpr Color hint_color = Color{25, 37, 30, 255};
	constexpr Color primary_color = Color{191, 203, 201, 255};

	constexpr int max_input_length = 4;
	char input[max_input_length + 1] = "";
	int inputLength = 0;
	char key;

	bool won = false;

	while (!WindowShouldClose())
	{
		key = GetCharPressed();
		// Loop if more than one key pressed on the same frame
		while (key > 0)
		{
			if ((key >= 32) && (key <= 122) && (inputLength < max_input_length))
			{
				input[inputLength] = key;
				inputLength++;
			}
			key = GetCharPressed();
		}
		if (IsKeyPressed(KEY_BACKSPACE) && (inputLength > 0))
		{
			inputLength--;
			input[inputLength] = '\0';
		}
		if (IsKeyPressed(KEY_ENTER) && (std::strcmp(input, "tuna") == 0))
		{
			won = true;
		}

		if (IsKeyPressed(KEY_ESCAPE) && !won)
		{
			break; // Exit to menu
		}

		BeginDrawing();
			ClearBackground(primary_color);

			// Draw table
			DrawRectangleRec(table_dimensions, Color{216, 202, 186, 255});

			// Draw the instructions
			DrawTextEx(
				hint_font,
				"This person really loves fish",
				Vector2{center_x - hint_dimensions.x / 2, 1000.0f},
				hint_size,
				hint_spacing,
				hint_color
			);

			// Draw safe
			DrawRectangleRounded(
				safe_dimensions,
				0.12f,
				0,
				Color{25, 37, 30, 255}
			);
			DrawRectangleRoundedLinesEx(
				safe_hole_dimensions,
				0.12f,
				0,
				3.0f,
				primary_color
			);
			for (int i = 0; i < max_input_length; i++)
			{
				DrawRectangle(
					safe_hole_padding + safe_hole_dimensions.x + i * (safe_slot_spacing + safe_slot_dimensions.x),
					safe_hole_dimensions.y + (safe_hole_dimensions.height - 70.0f) / 2,
					safe_slot_dimensions.x,
					safe_slot_dimensions.y,
					primary_color
				);
				DrawTextCodepoint(
					input_font,
					input[i],
					Vector2{safe_hole_padding + safe_hole_dimensions.x + i * (safe_slot_spacing + safe_slot_dimensions.x) + 25.0f, safe_hole_dimensions.y + (safe_hole_dimensions.height - 70.0f) / 2 + 25.0f},
					input_size,
					Color{25, 37, 30, 255}
				);
			}

			if (won)
			{
				switch (winMenu(hint_font, hint_size, hint_spacing))
				{
					case win: UnloadFont(input_font); UnloadFont(hint_font); return win;
					case win_and_exit_to_menu: UnloadFont(input_font); UnloadFont(hint_font); return win_and_exit_to_menu;
					default: break;
				}
			}
		EndDrawing();
	}
	UnloadFont(hint_font);
	UnloadFont(input_font);
	return exit_to_menu;
}