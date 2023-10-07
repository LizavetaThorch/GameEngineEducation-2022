#pragma once
#include "flecs.h"

struct Position
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

void register_ecs_phys_systems(flecs::world &ecs);

/* Данный код представляет объявления структур и функции, связанные с системами для физического моделирования объектов 
  в рамках ECS с использованием библиотеки flecs.
* Структуры "Position", "Velocity", "Gravity", "BouncePlane", "Bounciness", "ShiverAmount", "FrictionAmount" и "Radius" 
* определены для хранения соответствующих данных, связанных с физическим моделированием объектов.
* Также определен псевдоним типа "Speed", который является синонимом типа "float".
* Функция "register_ecs_phys_systems" объявлена, принимая ссылку на объект "flecs::world", представляющий ECS-мир
*/