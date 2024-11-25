#include "levels.h"

LevelEnd playLevel(int level)
{
	switch (level)
	{
		case 1: return level1();
		default: return invalid_level;
	}
}