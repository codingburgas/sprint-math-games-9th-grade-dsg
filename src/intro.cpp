#include "intro.h"
#include "raylib.h"

void playIntro()
{
    int frame = 0;

    const float font_size = 160.0f;
    const float font_spacing = 80.0f;
    Vector2 fieldSize = MeasureTextEx(GetFontDefault(), "********", font_size, font_spacing);
    // Add padding
    fieldSize.x += 200.0f;
    fieldSize.y += 50.0f;

    Vector2 passwordPosition = Vector2{(GetScreenWidth() - fieldSize.x) / 2 + 100.0f, 245.0f};

    float alpha = 1.0f;

    while (!WindowShouldClose())
    {
        if (GetKeyPressed() || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            return;

        frame++;
        if (frame >= 220)
            alpha -= 0.1f;

        BeginDrawing();
            ClearBackground(Color{217, 255, 224, 255});

            if (frame >= 165)
                DrawRectangleRoundedLinesEx(
                    Rectangle{(GetScreenWidth() - fieldSize.x) / 2, 220.0f, fieldSize.x, fieldSize.y},
                    0.1f,
                    0,
                    3.0f,
                    Fade(GREEN, alpha)
                );
            else
                DrawRectangleRoundedLinesEx(
                    Rectangle{(GetScreenWidth() - fieldSize.x) / 2, 220.0f, fieldSize.x, fieldSize.y},
                    0.1f,
                    0,
                    3.0f,
                    Fade(BLACK, alpha)
                );

            if (frame >= 145)
                DrawTextEx(GetFontDefault(), "********", passwordPosition, font_size, font_spacing, Fade(BLACK, alpha));
            else if (frame >= 120)
                DrawTextEx(GetFontDefault(), "*******", passwordPosition, font_size, font_spacing, BLACK);
            else if (frame >= 115)
                DrawTextEx(GetFontDefault(), "******", passwordPosition, font_size, font_spacing, BLACK);
            else if (frame >= 110)
                DrawTextEx(GetFontDefault(), "*****", passwordPosition, font_size, font_spacing, BLACK);
            else if (frame >= 100)
                DrawTextEx(GetFontDefault(), "****", passwordPosition, font_size, font_spacing, BLACK);
            else if (frame >= 85)
                DrawTextEx(GetFontDefault(), "***", passwordPosition, font_size, font_spacing, BLACK);
            else if (frame >= 75)
                DrawTextEx(GetFontDefault(), "**", passwordPosition, font_size, font_spacing, BLACK);
            else if (frame >= 60)
                DrawTextEx(GetFontDefault(), "*", passwordPosition, font_size, font_spacing, BLACK);
        EndDrawing();
    }

    CloseWindow();
}