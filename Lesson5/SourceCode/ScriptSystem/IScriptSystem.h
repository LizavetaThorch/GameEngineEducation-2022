//Интерфейс
// реализовывать не надо
#pragma once
#include "Common.h"

class IScriptProxy;

class SCRIPTSYSTEM_API IScriptSystem
{
public:
	virtual float Update(bool left, bool right, float deltaVel, float sp) = 0;
	virtual IScriptProxy* CreateProxy(const char* filename) = 0;
	virtual void ProcessScript(IScriptProxy* scriptProxy) = 0;
};
