#include "levels.h"
#include "raylib.h"
#include <cstring>
using namespace std;

LevelEnd level1()
{
	constexpr float window_y_padding = 100.0f;
	constexpr float phone_side_padding = 25.0f;

	const int center_x = GetScreenWidth() / 2;

	const int glow_x_position = center_x;
	const int glow_y_position = GetScreenHeight() / 2;

	const Rectangle phone_dimensions = Rectangle{
		center_x - GetScreenWidth() * 0.27f / 2,
		window_y_padding / 2,
		GetScreenWidth() * 0.27f,
		GetScreenHeight() - window_y_padding,
	};

	// Create text label variables
	constexpr float title_font_size    = 55.0f;
	constexpr float title_font_spacing = 8.0f;
	constexpr float text_font_size     = 40.0f;
	constexpr float text_font_spacing  = 6.0f;
	// Codepoints are null and codepointCount - 0 so the font applies to default characters
	const Font title_font = LoadFontEx("Inconsolata-Bold.ttf", title_font_size, nullptr, 0);
	const Vector2 title_label_size = MeasureTextEx(title_font, "Wi-Fi Connect", title_font_size, title_font_spacing);
	const Font phone_font = LoadFontEx("Inconsolata.ttf", text_font_size, nullptr, 0);
	const Font text_font = LoadFontEx("bBreakPassword.ttf", text_font_size, nullptr, 0);

	constexpr Color text_color = Color{25, 37, 30, 255};
	constexpr Color phone_text_color = Color{222, 239, 236, 255};
	constexpr Color secondary_color = Color{191, 203, 201, 255};

	constexpr int max_input_length = 12;
	char input[max_input_length + 1] = "";
	int inputLength = 0;
	char key;

	// To fade in instructions
	float alpha1 = 0.0f;
	float alpha2 = 0.0f;
	int frame = 0;
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
		if (IsKeyPressed(KEY_ENTER) && (std::strcmp(input, "12345678") == 0))
		{
			won = true;
		}

		if (IsKeyPressed(KEY_ESCAPE) && !won)
		{
			break; // Exit to menu
		}

		// Animate fade-in
		if (frame <= 100)
		{
			frame++;
		}
		else if (frame <= 250)
		{
			frame++;
			alpha1 += 0.05;
		}
		else if (frame <= 300)
		{
			frame++;
			alpha2 += 0.05;
		}

		BeginDrawing();
			ClearBackground(Color{197, 230, 224, 255});

			// Highlight phone with glow
			DrawCircleGradient(
				glow_x_position,
				glow_y_position,
				phone_dimensions.width / 2 + 200.0f,
				Color{255, 255, 255, 255},
				Color{255, 255, 255, 0}
			);

			// Draw the instructions
			DrawTextEx(
				text_font,
				"What was the\npassword again?",
				Vector2{120.0f, 300.0f},
				text_font_size,
				text_font_spacing,
				Fade(text_color, alpha1)
			);
			DrawTextEx(
				text_font,
				"The numbers\nfrom 1 to 8.",
				Vector2{1420.0f, 500.0f},
				text_font_size,
				text_font_spacing,
				Fade(text_color, alpha2)
			);

			// Draw phone screen background
			DrawRectangleRounded(
				phone_dimensions,
				0.12f,
				20,
				Color{25, 37, 30, 255}
			);
			// Draw phone UI
			DrawTextEx(
				title_font,
				"Wi-Fi Connect",
				Vector2{center_x - title_label_size.x / 2, phone_dimensions.y + 115.0f},
				title_font_size,
				title_font_spacing,
				phone_text_color
			);
			DrawTextEx(
				phone_font,
				"Password",
				Vector2{phone_dimensions.x + phone_side_padding, phone_dimensions.y + 350.0f},
				text_font_size,
				text_font_spacing,
				secondary_color
			);
			DrawLineEx(
				Vector2{phone_dimensions.x + phone_side_padding, phone_dimensions.y + 500.0f},
				Vector2{phone_dimensions.x + phone_dimensions.width - phone_side_padding, phone_dimensions.y + 500.0f},
				5.0f,
				Color{217, 255, 224, 255}
			);
			DrawTextEx(
				phone_font,
				input,
				Vector2{phone_dimensions.x + phone_side_padding, phone_dimensions.y + 445.0f},
				text_font_size,
				text_font_spacing,
				phone_text_color
			);

			// Draw phone border
			DrawRectangleRoundedLinesEx(
				phone_dimensions,
				0.12f,
				20,
				12.0f,
				Color{15, 36, 23, 255}
			);

			if (won)
			{
				switch (winMenu(text_font, text_font_size, text_font_spacing))
				{
					case win: UnloadFont(text_font); UnloadFont(phone_font); UnloadFont(title_font); return win;
					case win_and_exit_to_menu: UnloadFont(text_font); UnloadFont(phone_font); UnloadFont(title_font); return win_and_exit_to_menu;
					default: break;
				}
			}
		EndDrawing();
	}
	UnloadFont(title_font);
	UnloadFont(phone_font);
	UnloadFont(text_font);
	return exit_to_menu;
}