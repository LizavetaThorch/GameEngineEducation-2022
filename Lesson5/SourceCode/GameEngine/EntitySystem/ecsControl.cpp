#include "ecsControl.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "flecs.h"
#include "../InputHandler.h"
#include "../../ScriptSystem/IScriptSystem.h"


/*
* обрабатывает каждую сущность с компонентами "Velocity", "Speed" и "Controllable".
* Внутри функции каждой сущности происходит проверка состояния ввода, получаемого через запрос "inputQuery", 
* и обновление скорости объекта (vel.x) на основе входных данных
*/
void register_ecs_control_systems(flecs::world &ecs)
{
  static auto inputQuery = ecs.query<InputHandlerPtr>();
  static auto scriptQuery = ecs.query<IScriptSystemPtr>();

  //static ScriptSystem scriptSystem;
  ecs.system<Velocity, const Speed, const Controllable>()
    .each([&](flecs::entity e, Velocity &vel, const Speed &spd, const Controllable &)
    {
      inputQuery.each([&](InputHandlerPtr input)
      {
       bool left = input.ptr->GetInputState().test(eIC_GoLeft);
       bool right = input.ptr->GetInputState().test(eIC_GoRight);

        float deltaVel = 0.f;

        scriptQuery.each([&](IScriptSystemPtr scriptSystem)
            {
                vel.x += scriptSystem.ptr->Update(left, right, deltaVel, spd) * e.delta_time();
            }); 
      });
    });


/*
* обрабатывает каждую сущность с компонентами "Position", "Velocity", "Controllable", "BouncePlane" и "JumpSpeed". 
* Внутри функции каждой сущности происходит проверка состояния ввода, получаемого через запрос "inputQuery". 
* Если объект находится над плоскостью отскока (plane) в пределах заданного значения "plane.w + planeEpsilon", 
* и входное состояние содержит флаг для прыжка (eIC_Jump), то скорость объекта (vel.y) устанавливается на значение "jump.val".
*/
  ecs.system<const Position, Velocity, const Controllable, const BouncePlane, const JumpSpeed>()
    .each([&](const Position &pos, Velocity &vel, const Controllable &, const BouncePlane &plane, const JumpSpeed &jump)
    {
      inputQuery.each([&](InputHandlerPtr input)
      {
        constexpr float planeEpsilon = 0.1f;
        if (plane.x*pos.x + plane.y*pos.y + plane.z*pos.z < plane.w + planeEpsilon)
          if (input.ptr->GetInputState().test(eIC_Jump))
            vel.y = jump.val;
      });
    });
}

