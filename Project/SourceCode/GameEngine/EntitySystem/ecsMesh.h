#pragma once
#include "flecs.h"

struct CubeMesh {};
struct RenderProxyPtr
{
	class RenderProxy* ptr;
};

struct Color
{
	uint32_t color;
};

void register_ecs_mesh_systems(flecs::world &ecs);

