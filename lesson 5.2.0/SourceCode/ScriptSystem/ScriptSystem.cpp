// реализовать методы интрфейса IScriptSystem
#include "ScriptSystem.h"
#include "ScriptProxy.h"


CScriptSystem::CScriptSystem() // конструктор
{
    proxy = this->CreateProxy("../../Assets/scripts/movable.lua");
    return;
}


float CScriptSystem::Update(bool left, bool right, float deltaVel, float spd)
{
    return proxy->UpdateMovements(left, right, deltaVel, spd);
}

IScriptProxy* CScriptSystem::CreateProxy(const char* filename)
{
    // —оздаем экземпл€р класса ScriptProxy с указанным именем файла
    IScriptProxy* proxy = new CScriptProxy(filename);
    return proxy;
}


void CScriptSystem:: ProcessScript(IScriptProxy* scriptProxy)
{

}