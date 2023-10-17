#include "ecsMesh.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "flecs.h"
#include "RenderThread.h"
#include "RenderEngine.h"
#include "CubeRenderProxy.h"

/*
* Фун-ия обрабатывает каждую сущность с компонентом "CubeMesh". Внутри фун-ии каждой сущности происходит создание 
* объекта визуализации "renderProxy" типа "CubeRenderProxy". Затем, через запрос "renderQuery", происходит доступ 
* к экземпляру "RenderEnginePtr" для создания объекта визуализации и задания начальной позиции. После этого, экземпляр
* "renderProxy" связывается с сущностью через компонент "RenderProxyPtr", а компонент "CubeMesh" удаляется.
* Добавление const Position в фильтр и  позволяют системе создавать рендер-прокси для объектов, у которых есть 
* компонент const CubeMesh и const Position, и устанавливать их позицию на основе координат из const Position. 
* Затем компонент CubeMesh удаляется сущности e, чтобы избежать повторной обработки.
*/
void register_ecs_mesh_systems(flecs::world &ecs)
{
  static auto renderQuery = ecs.query<RenderEnginePtr>();
  ecs.system<const CubeMesh>()
    .each([&](flecs::entity e, const CubeMesh& cubeMesh)
    {
      renderQuery.each([&](RenderEnginePtr re)
      {
          RenderProxy* renderProxy = new CubeRenderProxy;
          re.ptr->GetRT()->EnqueueCommand(RC_CreateCubeRenderObject, renderProxy);

          float position[3];
          position[0] = 0.0f;
          position[1] = 0.0f;
          position[2] = 0.0f;

          renderProxy->SetPosition(position);

          e.set(RenderProxyPtr{ renderProxy });
          e.remove<CubeMesh>();
      });
    });

/*
* Фун-ия обрабатывает каждую сущность с компонентами "RenderProxyPtr" и "Position". Внутри функции каждой сущности 
* происходит доступ к экземпляру "RenderEnginePtr" и обновление позиции объекта визуализации на основе значений 
* компонента "Position". Общий контекст кода указывает на регистрацию и настройку систем для работы с визуализацией 
* трехмерных объектов в контексте ECS-архитектуры. Реализация данных систем может быть специфичной для вашего проекта
*  и требует дальнейшего изучения других компонентов и файлов.
*/
  ecs.system<RenderProxyPtr, const Position>()
    .each([&](RenderProxyPtr &renderProxy, const Position &pos)
    {
      renderQuery.each([&](RenderEnginePtr re)
      {
           float position[3];
           position[0] = pos.x;
           position[1] = pos.y;
           position[2] = pos.z;

           renderProxy.ptr->SetPosition(position);
      });
    });
}

