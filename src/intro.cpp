#include "intro.h"
#include "raylib.h"
#include "font.h"

void playIntro()
{
	int frame = 0;

	Vector2 fieldSize = MeasureTextEx(GetFontDefault(), "********", title_size, title_spacing);
	// Add padding
	constexpr float x_padding = 200.0f;
	constexpr float y_padding = 50.0f;
	fieldSize.x += x_padding;
	fieldSize.y += y_padding;
	constexpr float top_margin = 220.0f;

	const Vector2 password_position = Vector2{(GetScreenWidth() - fieldSize.x) / 2 + x_padding / 2, top_margin + y_padding / 2};

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
				DrawTextEx(GetFontDefault(), "********", password_position, title_size, title_spacing, Fade(BLACK, alpha));
			}
			else if (frame >= 120)
			{
				DrawTextEx(GetFontDefault(), "*******", password_position, title_size, title_spacing, BLACK);
			}
			else if (frame >= 115)
			{
				DrawTextEx(GetFontDefault(), "******", password_position, title_size, title_spacing, BLACK);
			}
			else if (frame >= 110)
			{
				DrawTextEx(GetFontDefault(), "*****", password_position, title_size, title_spacing, BLACK);
			}
			else if (frame >= 100)
			{
				DrawTextEx(GetFontDefault(), "****", password_position, title_size, title_spacing, BLACK);
			}
			else if (frame >= 85)
			{
				DrawTextEx(GetFontDefault(), "***", password_position, title_size, title_spacing, BLACK);
			}
			else if (frame >= 75)
			{
				DrawTextEx(GetFontDefault(), "**", password_position, title_size, title_spacing, BLACK);
			}
			else if (frame >= 60)
			{
				DrawTextEx(GetFontDefault(), "*", password_position, title_size, title_spacing, BLACK);
			}
		EndDrawing();
	}
}