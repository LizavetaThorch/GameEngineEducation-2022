#include "flecs.h"
#include "../../InputHandler.h"
#include "../ecsMesh.h"
#include "../ecsPhys.h"
#include "../ecsSystems.h"
#include "ecsParticle.h"

uint32_t interpolate(uint32_t color1, uint32_t color2, float fraction) {
    // abgr
    unsigned char a1 = (color1 >> 24) & 0xff;
    unsigned char a2 = (color2 >> 24) & 0xff;
    unsigned char b1 = (color1 >> 16) & 0xff;
    unsigned char b2 = (color2 >> 16) & 0xff;
    unsigned char g1 = (color1 >> 8) & 0xff;
    unsigned char g2 = (color2 >> 8) & 0xff;
    unsigned char r1 = color1 & 0xff;
    unsigned char r2 = color2 & 0xff;

    uint32_t r = static_cast<uint32_t>((1 - fraction) * r1 + fraction * r2) & 0xff;
    uint32_t g = static_cast<uint32_t>((1 - fraction) * g1 + fraction * g2) & 0xff;
    uint32_t b = static_cast<uint32_t>((1 - fraction) * b1 + fraction * b2) & 0xff;
    uint32_t a = static_cast<uint32_t>((1 - fraction) * a1 + fraction * a2) & 0xff;

    return (a << 24) | (b << 16) | (g << 8) | r;
}


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
                    .set(LifeTime{ emitter.lTime, emitter.lTime })
                    .set(ShiverAmount{ emitter.shiver })
                    .set(Color{ emitter.particle.startColor });
               
                if (emitter.randomRotation) {
                    particle.set(Rotation{
                        rand_flt(0, 6.283),
                        rand_flt(0, 6.283),
                        rand_flt(0, 6.283)
                        });
                }
                else {
                    particle.set(Rotation{
                        emitter.rotation.x,
                        emitter.rotation.y,
                        emitter.rotation.z
                        });
                }

                if (emitter.shape == ParticleEmitter::Shape::Cube) 
                {
                    particle.add<CubeMesh>();
                }
                emitter.timeSinceLastParticle = 0.0f;
            }
        });

    // Система изменения цвета и размера частицы
    ecs.system<Particle, Scale, Color, LifeTime>()
        .each([&](flecs::entity e, Particle& particle, Scale& scale, Color& color, LifeTime& lifetime) {
            float progress = (lifetime.totalLifeTime - lifetime.time) / lifetime.totalLifeTime;
            if (progress < 0) {
                progress = 0;
            }
            else if (progress > 1) {
                progress = 1;
            }

            color.color = interpolate(particle.startColor, particle.endColor, progress);

            scale.x = particle.startSize + progress * (particle.endSize - particle.startSize);
            scale.y = particle.startSize + progress * (particle.endSize - particle.startSize);
            scale.z = particle.startSize + progress * (particle.endSize - particle.startSize);
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
