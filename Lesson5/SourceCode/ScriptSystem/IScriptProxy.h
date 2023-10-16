#pragma once //запрещает заимпортить один и тот же код дважды
#include "Common.h"


class SCRIPTSYSTEM_API IScriptProxy
{
public:
	// написать метод из файла Lua
	virtual float UpdateMovements(bool left, bool right, float deltaVel, float spd) = 0;
};