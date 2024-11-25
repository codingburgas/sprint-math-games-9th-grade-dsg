#include "intro.h"
#include "raylib.h"

void playIntro()
{
	constexpr float font_size = 160.0f;
	constexpr float font_spacing = 50.0f;
	// Codepoints are null and codepointCount - 0 so the font applies to default characters
	const Font font = LoadFontEx("bBreakPassword.ttf", font_size, nullptr, 0);
	Vector2 fieldSize = MeasureTextEx(font, "********", font_size, font_spacing);
	// Add padding
	constexpr float x_padding = 200.0f;
	constexpr float y_padding = 50.0f;
	fieldSize.x += x_padding;
	fieldSize.y += y_padding;
	constexpr float top_margin = 220.0f;

	const Vector2 password_position = Vector2{(GetScreenWidth() - fieldSize.x) / 2 + x_padding / 2, top_margin + y_padding / 2};

	int frame = 0;
	float alpha = 1.0f;

	while (!WindowShouldClose() && !GetKeyPressed() && !IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && frame < 290) // Skip intro with mouse click or key press
	{
		frame++;
		if (frame >= 220)
		{
			alpha -= 0.1f;
		}

		BeginDrawing();
			ClearBackground(Color{217, 255, 224, 255});

			if (frame >= 165)
			{
				DrawRectangleRoundedLinesEx(
					Rectangle{(GetScreenWidth() - fieldSize.x) / 2, top_margin, fieldSize.x, fieldSize.y},
					0.1f,
					0,
					3.0f,
					Fade(GREEN, alpha)
				);
			}
			else
			{
				DrawRectangleRoundedLinesEx(
					Rectangle{(GetScreenWidth() - fieldSize.x) / 2, top_margin, fieldSize.x, fieldSize.y},
					0.1f,
					0,
					3.0f,
					Fade(BLACK, alpha)
				);
			}

			if (frame >= 145)
			{
				DrawTextEx(font, "********", password_position, font_size, font_spacing, Fade(BLACK, alpha));
			}
			else if (frame >= 120)
			{
				DrawTextEx(font, "*******", password_position, font_size, font_spacing, BLACK);
			}
			else if (frame >= 115)
			{
				DrawTextEx(font, "******", password_position, font_size, font_spacing, BLACK);
			}
			else if (frame >= 110)
			{
				DrawTextEx(font, "*****", password_position, font_size, font_spacing, BLACK);
			}
			else if (frame >= 100)
			{
				DrawTextEx(font, "****", password_position, font_size, font_spacing, BLACK);
			}
			else if (frame >= 85)
			{
				DrawTextEx(font, "***", password_position, font_size, font_spacing, BLACK);
			}
			else if (frame >= 75)
			{
				DrawTextEx(font, "**", password_position, font_size, font_spacing, BLACK);
			}
			else if (frame >= 60)
			{
				DrawTextEx(font, "*", password_position, font_size, font_spacing, BLACK);
			}
		EndDrawing();
	}
	UnloadFont(font);
}