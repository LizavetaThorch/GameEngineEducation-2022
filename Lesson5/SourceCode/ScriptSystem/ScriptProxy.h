#pragma once

#include <sol/sol.hpp>

#include "IScriptProxy.h"


class SCRIPTSYSTEM_API CScriptProxy final : public IScriptProxy
{
private:
	sol::state lua_script;
	sol::load_result sss;
public:
	CScriptProxy(const char* filename);
	virtual float UpdateMovements(bool left, bool right, float deltaVel, float spd) override;
};