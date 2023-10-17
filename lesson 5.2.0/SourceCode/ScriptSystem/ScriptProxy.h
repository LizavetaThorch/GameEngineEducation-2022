#pragma once

#include <sol/sol.hpp>

#include "IScriptProxy.h"


class SCRIPTSYSTEM_API CScriptProxy final : public IScriptProxy
{
private:
	sol::state lua_script;
	virtual float UpdateMovements(bool left = false, bool right = false, float deltaVel = 0.f, float spd = 0.f) override;
public:
	CScriptProxy(const char* filename);
};