#pragma once

#include <sol/sol.hpp>
#include "ScriptProxy.h"

CScriptProxy::CScriptProxy(const char* filename)
{
    lua_script.script_file(filename);
}

float CScriptProxy::UpdateMovements(bool left, bool right, float deltaVel, float spd)
{
    return lua_script["UpdateMovements"](left, right, deltaVel, spd);
}
