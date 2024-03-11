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
    1.f, //float lTime
    100.f, //float frequency
    {0.0f, 2.5f, 0.f}, //Velocity vel
    {0.05f, 0.07f, 0.06f},//RotationVelocity rotVel;
    true, //bool randomRotation;
    {0.f, 0.f, 0.f},//Rotation rotation;
    {0.f, 0.f, 0.f},//Gravity gravity;
    ParticleEmitter::Shape::Cube, //Shape shape;
    {0.1f}, //ShiverAmount shiver;
    {0.25f, 0.1f, 0xff808080, 0x88ffffff }, //Particle particle; #FF69B4 =>   #C71585 => 0xff8515c7   0xffd3d3d3
};

const ParticleEmitter PARTICLE_EMITTER_PRESET_FIRE
{
    // Particle Emitter
    1.2f, //float lTime
    20.f, //float frequency
    {0.2f, 5.f, 0.f}, //Velocity vel
    {0.0f, 0.0f, 0.5f},//RotationVelocity rotVel;
    false,//bool randomRotation;
    {0.f, 0.f, 1.f},//Rotation rotation;
    {0.f, -0.02f, 0.f},//Gravity gravity;
    ParticleEmitter::Shape::Cube, //Shape shape;
    {0.00f}, //ShiverAmount shiver;
    {0.7f, 0.01f, 0x0000ff, 0xff00ffff }, //Particle particle;  #C71585 => 0xff8515c7  0xff0045ff (orange red)
};

const ParticleEmitter PARTICLE_EMITTER_PRESET_SNOW
{
    // Particle Emitter
    1.2f, //float lTime
    600.f, //float frequency
    {0.2f, -5.f, 0.f}, //Velocity vel
    {0.0f, 0.5f, 0.5f},//RotationVelocity rotVel;
    false,//bool randomRotation;
    {0.f, 0.f, 1.f},//Rotation rotation;
    {0.f, -0.06f, 0.f},//Gravity gravity;
    ParticleEmitter::Shape::Cube, //Shape shape;
    {0.00f}, //ShiverAmount shiver;
    {0.09f, 0.01f, 0xffb48246, 0xffffffe0 }, //Particle particle;  #C71585 => 0xff8515c7
};


uint32_t interpolate(uint32_t color1, uint32_t color2, float fraction);

void register_ecs_particle_systems(flecs::world& ecs);

flecs::entity createParticleEmitter(flecs::world& ecs, const EmitterSetting& settings);