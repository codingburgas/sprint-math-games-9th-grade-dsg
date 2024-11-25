#pragma once

// Defines how a level has ended. Returned by all level functions.
enum LevelEnd
{
	exit_to_menu,
	win,
	win_and_exit_to_menu,
	invalid_level
};

LevelEnd playLevel(int);
LevelEnd level1();