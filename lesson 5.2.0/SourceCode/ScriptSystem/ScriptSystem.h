#pragma once
#include "IScriptSystem.h"

class SCRIPTSYSTEM_API CScriptSystem final : public IScriptSystem {
private:
	IScriptProxy* proxy;

public:
	CScriptSystem();

	virtual float Update(bool left = false, bool right = false, float deltaVel = 0.f, float sp = 0.f) override;
	virtual IScriptProxy* CreateProxy(const char* filename) override;
	virtual void ProcessScript(IScriptProxy* scriptProxy) override;
};