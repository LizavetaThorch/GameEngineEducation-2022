#pragma once
#include "flecs.h"

void register_ecs_shoot_systems(flecs::world& ecs);

struct InputState { bool shoot = false; };

struct Shoot { 
	int shotsCapacity; 
	bool reloading = false; 
	int shots;
	float currentTime;
	float timeBetweenShots;
};

struct Bullet { };
   

