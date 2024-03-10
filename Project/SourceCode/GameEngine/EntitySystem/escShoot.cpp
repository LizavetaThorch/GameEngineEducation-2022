#include "flecs.h"
#include "ecsMesh.h"
#include "ecsPhys.h"
#include "escShoot.h"
#include "ecsSystems.h"
#include "../InputHandler.h"


void register_ecs_shoot_systems(flecs::world& ecs)
{
    // 3 функции: отвечает за создание шариков(пистолет) + перезаряд(пистолета); уничтожение шариков; отскок

    static auto inputQuery = ecs.query<InputHandlerPtr>();

   ecs.system<InputState>()
        .each([&](InputState& state) {
            inputQuery.each([&](InputHandlerPtr& input) {
                state.shoot = input.ptr->GetInputState().test(eIC_Shoot);// разыменование указателя с обращением к полю
            });
        });

    // Система выстрелов
    ecs.system<InputState, Shoot, const Position>()
        .each([&](flecs::entity e, const InputState& state, Shoot& sh, const Position& pos) {
        // Проверяем, нажата ли кнопка выстрела и не находится ли она в процессе перезарядки
        if (state.shoot && !sh.reloading) {
            // Выстрелить пулей
            e.world().entity()
                .set(Position{ pos })
                .set(Velocity{ 2.5f, 0, 0 })
                .set(Gravity{ 0, -9.8, 0 })
                .set(BouncePlane{ 0, 1, 0, 0 })
                .set(Bounciness{ 0.4f })
                .add<Bullet>()
                .set(LifeTime{ 5.0f, false })
                .set(FrictionAmount{ 0.2f })
                .add<CubeMesh>();

            // Уменьшить количество оставшихся выстрелов
            sh.shots--;
        }
        // Проверяем, достигло ли количество оставшихся выстрелов нуля
        // Пустой - начать перезарядку
        if (sh.shots <= 0 && !sh.reloading) {
            // Начать перезарядку
            sh.reloading = true;
            sh.currentTime = sh.timeBetweenShots;
        }
        // Пустой - процесс перезарядки
        if (sh.reloading) {
            sh.currentTime -= e.delta_time();
        }
        // Пустой - закончить перезарядку
        if (sh.reloading && sh.currentTime <= 0.0f) {
            sh.shots = sh.shotsCapacity; // обновить шарики
            sh.reloading = false;
        }
            });


    // Система уничтожения шаров
    ecs.system<const Position, const BouncePlane, Bullet, LifeTime, RenderProxyPtr>()
        .each([&](flecs::entity e, const Position& pos, const BouncePlane& plane, Bullet& bullet, LifeTime& lifetime,
          const RenderProxyPtr& proxy) {
        // Проверяем, столкнулся ли шарик с землей
        if (plane.x * pos.x + plane.y * pos.y + plane.z * pos.z < plane.w + 0.11) {
            lifetime.started = true;
        }
    });
}