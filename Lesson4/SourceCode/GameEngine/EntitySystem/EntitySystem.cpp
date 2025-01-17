#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"
#include "escShoot.h"

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

/*
добавление auto target и auto bullet позволит создать и настроить сущности "target" и "bullet",
что предоставит функционал для работы с целями и оружием внутри вашей игры
*/      

    auto cubeControl = ecs.entity()
        .set(Position{ 0.f, 0.f, 0.f })
        .set(Velocity{ 0.f, 0.f, 0.f })
        .set(Speed{ 10.f })
        .set(FrictionAmount{ 0.9f })
        .set(JumpSpeed{ 10.f })
        .set(Gravity{ 0.f, -9.8065f, 0.f })
        .set(BouncePlane{ 0.f, 1.f, 0.f, 0.f })
        .set(Shoot{ 6, false, 6, 0, 2.0f })
        .set(InputState{ false })
        .set(Bounciness{ 0.3f })
        .add<Controllable>()
        .add<CubeMesh>();

    auto cubeMoving = ecs.entity()
        .set(Position{ 0.f, 0.f, 0.f })
        .set(Velocity{ 0.f, 3.f, 0.f })
        .set(Gravity{ 0.f, -9.8065f, 0.f })
        .set(BouncePlane{ 0.f, 1.f, 0.f, 5.f })
        .set(Bounciness{ 1.f })
        .add<CubeMesh>();
}

void EntitySystem::Update()
{
    ecs.progress();
}

/*
* Общий контекст кода указывает на то, что класс "EntitySystem" соединяет различные системы и сущности
* для управления игровыми объектами, и позволяет обновлять их состояние на каждом шаге обновления игры
*/