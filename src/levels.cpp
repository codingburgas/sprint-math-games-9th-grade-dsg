#include "levels.h"

LevelEnd playLevel(int level)
{
	switch (level)
	{
		case 1: return level1();
		case 2: return level2();
		default: return invalid_level;
	}
}