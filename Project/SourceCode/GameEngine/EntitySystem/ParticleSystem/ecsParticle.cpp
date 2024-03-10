#include "flecs.h"
#include "../../InputHandler.h"
#include "../ecsMesh.h"
#include "../ecsPhys.h"
#include "../ecsSystems.h"
#include "ecsParticle.h"


void register_ecs_particle_systems(flecs::world& ecs)
{
    ecs.system<ParticleEmitter, const Position, const Scale>()
        .each([&](flecs::entity e, ParticleEmitter &emitter, const Position &pos, const Scale &scale) {
              
            emitter.timeSinceLastParticle += e.delta_time();

            if (emitter.timeSinceLastParticle >= 1.0f / emitter.frequency)
            {
                auto particle = e.world().entity()
                    .set(Particle{ emitter.particle.startSize, emitter.particle.endSize, emitter.particle.startColor, emitter.particle.endColor })
                    .set(Position{ 
                        rand_flt(pos.x - scale.x, pos.x + scale.x), 
                        rand_flt(pos.y - scale.y, pos.y + scale.y),
                        rand_flt(pos.z - scale.z, pos.z + scale.z) 
                    })
                    .set(Scale{ emitter.particle.startSize, emitter.particle.startSize, emitter.particle.startSize })
                    .set(Rotation{
                        rand_flt(0, 6.283),
                        rand_flt(0, 6.283),
                        rand_flt(0, 6.283)
                    })
                    .set(Velocity{ emitter.vel })
                    .set(RotationVelocity{ emitter.rotVel })
                    .set(Gravity{ emitter.gravity })
                    .set(LifeTime{ emitter.lTime })
                    .set(ShiverAmount{ emitter.shiver })
                    .set(Color{ emitter.particle.startColor });
                      
                if (emitter.shape == ParticleEmitter::Shape::Cube) 
                {
                    particle.add<CubeMesh>();
                }
                emitter.timeSinceLastParticle = 0.0f;
            }

        
        });
}

flecs::entity createParticleEmitter(flecs::world& ecs, const EmitterSetting& settings)
{
    return ecs.entity()
        .set(ParticleEmitter{ settings.particleEmitter })
        .set(Position{ settings.position })
        .set(Scale{ settings.scale })
        .set(ObjectId{ settings.id });
}