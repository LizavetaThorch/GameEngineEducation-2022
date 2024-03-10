#pragma once 

#include "Particle.h"
#include "../ecsPhys.h"

struct ParticleEmitter
{
	float lTime;
	float frequency; // часота появления
	Velocity vel;
	RotationVelocity rotVel;
	bool randomRotation;
	Rotation rotation;
	Gravity gravity;

	enum class Shape
	{
		Cube
	};

	Shape shape;
	ShiverAmount shiver;
	
	Particle particle;

	float timeSinceLastParticle = 0.f;
};

struct ObjectId
{
	int id;
};
