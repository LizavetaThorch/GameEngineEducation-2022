#pragma once

#include <sol/sol.hpp>
#include "ScriptProxy.h"

CScriptProxy::CScriptProxy(const char* filename)
{
    // ������� ��������� Lua-���������
    lua_script.open_libraries(sol::lib::base);

    // ��������� ���������� ����
    std::string filepath = "../../Assets/scripts/movable.lua";
    lua_script.script_file(filepath);

    // ������������ ������� UpdateMovements �� Lua-�������
    lua_script.set_function("UpdateMovements", &CScriptProxy::UpdateMovements, this);
}

float CScriptProxy::UpdateMovements(bool left, bool right, float deltaVel, float spd)
{
    sol::protected_function movement;
    if(left){
        movement = lua_script["MoveLeft"];
    }
    else if(right) {
        movement = lua_script["MoveRight"];
    }
    else {
        movement = lua_script["Pause"];
    }
    std::optional<float> move = movement(left, right, deltaVel, spd);
    return move.has_value();
}
