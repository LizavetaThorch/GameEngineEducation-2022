#include "ecsMesh.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "flecs.h"
#include "RenderThread.h"
#include "RenderEngine.h"
#include "CubeRenderProxy.h"


void updateRenderProxy(RenderProxy* renderProxy, const Position& pos, const Rotation& angle, const Scale& sc, const Color& color) 
{
    float position[3];
    position[0] = pos.x;
    position[1] = pos.y;
    position[2] = pos.z;

    float scale[3];
    scale[0] = sc.x;
    scale[1] = sc.y;
    scale[2] = sc.z;

    float rotation[3];
    rotation[0] = angle.x;
    rotation[1] = angle.y;
    rotation[2] = angle.z;

    renderProxy->SetPosition(position);
    renderProxy->SetScale(scale);
    renderProxy->SetRotationAngle(rotation);
    renderProxy->SetColor(color.color);
}

void register_ecs_mesh_systems(flecs::world &ecs)
{
  static auto renderQuery = ecs.query<RenderEnginePtr>();
  ecs.system<const CubeMesh, const Position, const Rotation, const Scale, const Color>()
    .each([&](flecs::entity e, const CubeMesh& cubeMesh, const Position& pos, const Rotation& angle, const Scale& sc, const Color& color)
    {
      renderQuery.each([&](RenderEnginePtr re)
      {
          RenderProxy* renderProxy = new CubeRenderProxy;
          re.ptr->GetRT()->EnqueueCommand(RC_CreateCubeRenderObject, renderProxy);

          updateRenderProxy(renderProxy, pos, angle, sc, color);

          e.set(RenderProxyPtr{ renderProxy });
          e.remove<CubeMesh>();
      });
    });

  ecs.system<RenderProxyPtr, const Position, const Rotation, const Scale, const Color>()
    .each([&](RenderProxyPtr &renderProxy, const Position &pos, const Rotation &angle, const Scale &sc, const Color &color)
    {
      renderQuery.each([&](RenderEnginePtr re)
      {
           updateRenderProxy(renderProxy.ptr, pos, angle, sc, color);
      });
    });
}
