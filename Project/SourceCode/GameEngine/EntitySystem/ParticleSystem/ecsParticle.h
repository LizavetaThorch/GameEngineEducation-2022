#pragma once

#include "flecs.h"
#include "Particle.h"
#include "../ecsPhys.h"
#include "ParticleEmitter.h"

struct EmitterSetting
{
	ParticleEmitter particleEmitter;
	Position position{ 0.f, 0.f, 0.f };
	Scale scale{ 1.0f, 1.0f, 1.0f };
    ObjectId id{ 0 };
};

const ParticleEmitter PARTICLE_EMITTER_PRESET_SMOKE
{
    // Particle Emitter
    1.2f, //float lTime
    30.f, //float frequency
    {0.2f, 1.f, 0.f}, //Velocity vel
    {0.f, 0.f, 0.f},//RotationVelocity rotVel;
    false,//bool randomRotation;
    {5.f, 3.f, 8.f},//Rotation rotation;
    {0.f, -0.01f, 0.f},//Gravity gravity;
    ParticleEmitter::Shape::Cube, //Shape shape;
    {0.05f}, //ShiverAmount shiver;
    {0.3f, 0.02f, 0xff808080, 0xffd3d3d3 }, //Particle particle; #FF69B4 =>   #C71585 => 0xff8515c7
};

const ParticleEmitter PARTICLE_EMITTER_PRESET_FIRE
{
    // Particle Emitter
    1.2f, //float lTime
    50.f, //float frequency
    {0.2f, 2.f, 0.f}, //Velocity vel
    {0.f, 0.f, 0.f},//RotationVelocity rotVel;
    false,//bool randomRotation;
    {5.f, 3.f, 8.f},//Rotation rotation;
    {0.f, -0.00f, 0.f},//Gravity gravity;
    ParticleEmitter::Shape::Cube, //Shape shape;
    {0.05f}, //ShiverAmount shiver;
    {0.1f, 0.02f, 0xff0000ff, 0xffd3d3d3 }, //Particle particle; #FF69B4 =>   #C71585 => 0xff8515c7
};

void register_ecs_particle_systems(flecs::world& ecs);

flecs::entity createParticleEmitter(flecs::world& ecs, const EmitterSetting& settings);