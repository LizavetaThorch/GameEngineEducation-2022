#pragma once

#include <sol/sol.hpp>
#include "ScriptProxy.h"

CScriptProxy::CScriptProxy(const char* filename)
{
    // Создаем экземпляр Lua-состояния
    lua_script.open_libraries(sol::lib::base);

    // Загружаем скриптовый файл
    std::string filepath = "../../Assets/scripts/movable.lua";
    lua_script.script_file(filepath);

    // Регистрируем функцию UpdateMovements из Lua-скрипта
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
