#include "ecsPhys.h"
#include <stdlib.h>
#include "ecsMesh.h"



float rand_flt(float from, float to)
{
  return from + (float(rand()) / RAND_MAX) * (to - from);
}

void register_ecs_phys_systems(flecs::world& ecs)
{
    ecs.system<Velocity, const Gravity, BouncePlane*, Position*>()
        .each([&](flecs::entity e, Velocity& vel, const Gravity& grav, BouncePlane* plane, Position* pos)
            {
                if (plane && pos)
                {
                    constexpr float planeEpsilon = 0.1f;
                    if (plane->x * pos->x + plane->y * pos->y + plane->z * pos->z < plane->w + planeEpsilon)
                        return;
                }
                vel.x += grav.x * e.delta_time();
                vel.y += grav.y * e.delta_time();
                vel.z += grav.z * e.delta_time();
            });

    ecs.system<Velocity, Position, const BouncePlane, const Bounciness>()
        .each([&](Velocity& vel, Position& pos, const BouncePlane& plane, const Bounciness& bounciness)
            {
                float dotPos = plane.x * pos.x + plane.y * pos.y + plane.z * pos.z;
                float dotVel = plane.x * vel.x + plane.y * vel.y + plane.z * vel.z;
                if (dotPos < plane.w)
                {
                    pos.x -= (dotPos - plane.w) * plane.x;
                    pos.y -= (dotPos - plane.w) * plane.y;
                    pos.z -= (dotPos - plane.w) * plane.z;

                    vel.x -= (1.f + bounciness.val) * plane.x * dotVel;
                    vel.y -= (1.f + bounciness.val) * plane.y * dotVel;
                    vel.z -= (1.f + bounciness.val) * plane.z * dotVel;
                }
            });

    ecs.system<Velocity, const FrictionAmount>()
        .each([&](flecs::entity e, Velocity& vel, const FrictionAmount& friction)
            {
                vel.x -= vel.x * friction.val * e.delta_time();
                vel.y -= vel.y * friction.val * e.delta_time();
                vel.z -= vel.z * friction.val * e.delta_time();
            });

    ecs.system<Position, const Velocity>()
        .each([&](flecs::entity e, Position& pos, const Velocity& vel)
            {
                pos.x += vel.x * e.delta_time();
                pos.y += vel.y * e.delta_time();
                pos.z += vel.z * e.delta_time();
            });

    ecs.system<Velocity, const ShiverAmount>()
        .each([&](flecs::entity e, Velocity& vel, const ShiverAmount& shiver)
            {
                vel.x += rand_flt(-shiver.val, shiver.val);
                vel.y += rand_flt(-shiver.val, shiver.val);
                vel.z += rand_flt(-shiver.val, shiver.val);
            });

    // Отложить уничтожение шара на 5 секунд
    ecs.system<LifeTime, RenderProxyPtr>()
        .each([&](flecs::entity e, LifeTime& time, const RenderProxyPtr& proxy)
        {
            if (time.started) {
                time.time -= e.delta_time();
            }
            if (time.time <= 0.0f) {
                e.destruct();
                delete proxy.ptr;
            }
        });

   ecs.system<Rotation, const RotationVelocity>()
        .each([&](flecs::entity e, Rotation &rotation, const RotationVelocity &rotVel)
        {
                rotation.x += rotVel.x;
                rotation.y += rotVel.y;
                rotation.z += rotVel.z;
        });
}

