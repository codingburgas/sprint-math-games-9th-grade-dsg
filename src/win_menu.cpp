#include "raylib.h"
#include "levels.h"

LevelEnd winMenu(Font font, float font_size, float font_spacing)
{
	const Rectangle win_menu_dimensions = Rectangle{
		(GetScreenWidth() - GetScreenWidth() * 0.33f) / 2,
		(GetScreenHeight() - GetScreenHeight() * 0.45f) / 2,
		GetScreenWidth() * 0.33f,
		GetScreenHeight() * 0.45f,
	};

	constexpr float button_margin = 65.0f;
	constexpr float button_padding = 35.0f;
	const Rectangle menu_button_dimensions = Rectangle{
		win_menu_dimensions.x + button_margin,
		win_menu_dimensions.y + 4 * button_margin,
		200.0f,
		100.0f
	};
	const Rectangle next_button_dimensions = Rectangle{
		win_menu_dimensions.x + win_menu_dimensions.width - 200.0f - button_margin,
		win_menu_dimensions.y + 4 * button_margin,
		200.0f,
		100.0f
	};

	const Vector2 win_title_size = MeasureTextEx(font, "You Win!", font_size, font_spacing);

	constexpr Color text_color = Color{25, 37, 30, 255};
	Color menuButtonColor = text_color;
	Color nextButtonColor = text_color;

	if (CheckCollisionPointRec(GetMousePosition(), menu_button_dimensions))
	{
		menuButtonColor = MAROON;
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			return win_and_exit_to_menu;
		}
	}
	else
	{
		menuButtonColor = text_color;
	}

	if (CheckCollisionPointRec(GetMousePosition(), next_button_dimensions))
	{
		nextButtonColor = DARKGREEN;
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			return win;
		}
	}
	else
	{
		nextButtonColor = text_color;
	}

	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{255, 255, 255, 100});
	DrawRectangleRec(win_menu_dimensions, Color{191, 203, 201, 255});

	DrawTextEx(
		font,
		"You Win!",
		Vector2{(GetScreenWidth() - win_title_size.x) / 2, win_menu_dimensions.y + 100.0f},
		font_size,
		font_spacing,
		text_color
	);

	// Menu button
	DrawRectangleRoundedLinesEx(
		menu_button_dimensions,
		0.1f,
		0,
		3.0f,
		menuButtonColor
	);
	DrawTextEx(
		font,
		"Menu",
		Vector2{menu_button_dimensions.x + button_padding, menu_button_dimensions.y + button_padding},
		font_size,
		font_spacing,
		menuButtonColor
	);

	// Next button
	DrawRectangleRoundedLinesEx(
		next_button_dimensions,
		0.1f,
		0,
		3.0f,
		nextButtonColor
	);
	DrawTextEx(
		font,
		"Next",
		Vector2{next_button_dimensions.x + button_padding + 18.0f, next_button_dimensions.y + button_padding},
		font_size,
		font_spacing,
		nextButtonColor
	);
	return invalid_level;
}