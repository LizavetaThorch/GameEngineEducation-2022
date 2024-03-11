#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"
#include "escShoot.h"
#include "ParticleSystem/ecsParticle.h"


EntitySystem::EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler)
{
    ecs.entity("inputHandler")
        .set(InputHandlerPtr{ inputHandler });
    ecs.entity("renderEngine")
        .set(RenderEnginePtr{ renderEngine });

    register_ecs_mesh_systems(ecs);
    register_ecs_control_systems(ecs);
    register_ecs_phys_systems(ecs);
    register_ecs_shoot_systems(ecs);
    register_ecs_particle_systems(ecs);
     
    /*auto floor = ecs.entity()
        .set(Position{ 0.f, -2.0f, 0.f })
        .set(Scale{ 10.f, 1.f, 10.f })
        .set(Rotation{ 0.f, 0.f, 0.f })
        .set(Color{ 0xff228811 })
        .add<CubeMesh>();*/

    auto cubeControl = ecs.entity()
        .set(Position{ -1.f, 0.0f, 0.f })
        .set(Scale{ 1.f, 1.f, 1.f })
        .set(Rotation{ 0.f, 0.f, 0.f })
        .set(Color{ 0xffffff00 })
        .set(Velocity{ 0.f, 0.f, 0.f })
        .set(Speed{ 10.f })
        .set(FrictionAmount{ 0.9f })
        .set(JumpSpeed{ 10.f })
        .set(Gravity{ 0.f, -9.8065f, 0.f })
        .set(BouncePlane{ 0.f, 1.f, 0.f, 0.f })
        .set(Shoot{ 6, false, 6, 0, 0.5f })
        .set(InputState{ false })
        .set(Bounciness{ 0.3f })
        .add<Controllable>()
        .add<CubeMesh>();

    //auto particleEmitterSmoke = createParticleEmitter(ecs, {
    //    PARTICLE_EMITTER_PRESET_SMOKE,
    //    { 0.f, 1.f, 0.f }, // Position
    //    { 1.f, 0.f, 1.f }, // Scale
    //    { 1 } // ID
    //});

    //auto particleEmitterFire = createParticleEmitter(ecs, {
    //    PARTICLE_EMITTER_PRESET_FIRE,
    //    { 0.f, -1.f, 0.f }, // Position
    //    { 1.f, 0.f, 1.f } // Scale
    //    });

    auto particleEmitterSnow = createParticleEmitter(ecs, {
        PARTICLE_EMITTER_PRESET_SNOW,
        { 0.f, 5.f, 0.f }, // Position
        { 5.f, 5.f, 5.f } // Scale
        });

    // �������� �������� � ������� (������������ �������������� ������ ����� ������� � ������ ������� ���������). ��� �������� ������������ id
    static auto emitterQuery = ecs.query<const ObjectId, Position>();

    ecs.system<const Controllable, const Position, const Scale>()
        .each([&](flecs::entity e, const Controllable& object, const Position& objectPosition, const Scale& objectScale) {
        emitterQuery.each([&](const ObjectId& id, Position& position) {
            if (id.id == 1) {
                position.x = objectPosition.x;
                position.y = objectPosition.y + objectScale.y;
                position.z = objectPosition.z;
            }
        });
    });


}

void EntitySystem::Update()
{
    ecs.progress();
}