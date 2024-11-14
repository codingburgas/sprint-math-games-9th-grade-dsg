#include "raylib.h"
#include "resource_dir.h"	// for SearchAndSetResourceDir
#include <algorithm>
using namespace std;

int main()
{
	const int gameWidth = 1920;
	const int gameHeight = 1080;
	float scale;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
	InitWindow(gameWidth, gameHeight, "Parolino");

	// Allows the game to respond to the window resizing
	RenderTexture2D target = LoadRenderTexture(gameWidth, gameHeight);
	SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

	SetTargetFPS(60);

	// Game loop
	while (!WindowShouldClose())	// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		scale = min((float)GetScreenWidth() / gameWidth, (float)GetScreenHeight() / gameHeight);

		// Draw everything in the render texture
		BeginTextureMode(target);
			ClearBackground(Color{217, 253, 255, 255});

			// Title
			DrawText("Parolino", gameWidth / 2 - MeasureText("Parolino", 64) / 2, 200, 64, Color{0, 20, 8, 255});

		EndTextureMode();

		// Draw finished render texture
		BeginDrawing();
			ClearBackground(BLACK);

			DrawTexturePro(
				target.texture,
				Rectangle{0.0, 0.0, (float)target.texture.width, (float)-target.texture.height},
				Rectangle{(GetScreenWidth() - ((float)gameWidth * scale)) * 0.5f, (GetScreenHeight() - ((float)gameHeight * scale)) * 0.5f, gameWidth * scale, gameHeight * scale},
				Vector2{0, 0},
				0.0f,
				WHITE
			);

		EndDrawing();
	}

	UnloadRenderTexture(target);

	// destory the window and cleanup the OpenGL context
	CloseWindow();
}