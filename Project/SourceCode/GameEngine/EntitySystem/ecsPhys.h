#pragma once
#include "flecs.h"

struct Position
{
	float x, y, z;
};

struct Scale 
{
	float x, y, z;
};

struct Rotation
{
	float x, y, z;
};

struct RotationVelocity
{
	float x, y, z;
};

struct Velocity
{
	float x, y, z;
};

struct Gravity
{
	float x, y, z;
};

struct BouncePlane
{
  float x,y,z,w;
};

struct Bounciness
{
  float val;
};

struct ShiverAmount
{
  float val;
};

struct FrictionAmount
{
  float val;
};

typedef float Speed;

struct LifeTime
{
	float time = 5.0f;  // время существования частицы
	bool started = true;
};

void register_ecs_phys_systems(flecs::world &ecs);

float rand_flt(float from, float to);