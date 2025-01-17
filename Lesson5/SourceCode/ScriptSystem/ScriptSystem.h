#pragma once
#include "IScriptSystem.h"

class SCRIPTSYSTEM_API CScriptSystem final : public IScriptSystem {
private:
	IScriptProxy* proxy;

public:
	CScriptSystem();

	virtual float Update(bool left, bool right, float deltaVel, float spd) override;
	virtual IScriptProxy* CreateProxy(const char* filename) override;
	virtual void ProcessScript(IScriptProxy* scriptProxy) override;
};