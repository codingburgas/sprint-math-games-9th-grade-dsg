#pragma once
#include "raylib.h"

// Defines how a level has ended. Returned by all level functions.
enum LevelEnd
{
	exit_to_menu,
	win,
	win_and_exit_to_menu,
	invalid_level
};

LevelEnd playLevel(int);
// Displays the win menu in a given font to not unload a font every call
LevelEnd winMenu(Font, float, float);

LevelEnd level1();
LevelEnd level2();