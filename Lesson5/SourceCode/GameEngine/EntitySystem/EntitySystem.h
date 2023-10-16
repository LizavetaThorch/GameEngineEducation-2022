#pragma once

#include "flecs.h"
#include "RenderEngine.h"
#include "../InputHandler.h"
#include "../../ScriptSystem/ScriptSystem.h"

class EntitySystem
{
public:
	EntitySystem() = delete;
	EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler, IScriptSystem* scriptSystem);

	void Update();
private:
	flecs::world ecs;
};

