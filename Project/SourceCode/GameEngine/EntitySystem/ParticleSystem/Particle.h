#pragma once 

struct Particle
{
	float startSize;
	float endSize;

	uint32_t startColor;
	uint32_t endColor;
};



// Particle -- это сущность, которая обладает такими свойствами, как жизенный цикл(lifetime) 
// и какой вид она имеет (вода, огонь, магия, дым)

// Particle, LifeTime, Position, Velocity, Gravity (выставлять для таких типов как: магия, вода)
// Добавить size для частиц