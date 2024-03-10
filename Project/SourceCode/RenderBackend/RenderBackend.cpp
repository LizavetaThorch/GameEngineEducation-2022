#include <bx/math.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <cassert>

#include "RenderBackend.h"
#include "BgfxRenderData.h"

void RenderBackend::Init()
{
	bgfx::renderFrame();

	bgfx::Init bgfxInit;
	bgfxInit.type = bgfx::RendererType::Direct3D11;
	bgfxInit.resolution.width = 800;
	bgfxInit.resolution.height = 600;
	bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
	bgfxInit.platformData.nwh = m_windowHandle;
	if (!bgfx::init(bgfxInit))
		assert(0);

	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
	bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
}

void RenderBackend::SetWindowHandle(void* windowHandle)
{
	m_windowHandle = windowHandle;
}

IRenderData* RenderBackend::CreateRenderObject(
	void* vertices, UINT32 verticesSize,
	void* indices, UINT32 indicesSize,
	std::string vsShaderName, std::string psShaderName)
{
	BgfxRenderData* renderData = new BgfxRenderData(
		vertices, verticesSize,
		indices, indicesSize,
		vsShaderName, psShaderName);
	return renderData;
}

void RenderBackend::SetViewTransform()
{
	const bx::Vec3 at = { 0.0f, 0.0f,  0.0f };
	const bx::Vec3 eye = { 3.0f, 5.0f, -10.0f };
	float view[16];
	bx::mtxLookAt(view, eye, at);
	float proj[16];
	bx::mtxProj(proj, 60.0f, float(800) / float(600), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
	bgfx::setViewTransform(0, view, proj);
}

void RenderBackend::Draw(IRenderData* renderObject) // Создание матриц
{
	assert(renderObject);

	float mtx[16];
	bx::mtxRotateXYZ(mtx, 0, 0, 0);

	float scale[3] = { 1.0f, 1.0f, 1.0f }; // Масштаб по умолчанию
	renderObject->GetScale(scale);
	
	float rotationAngle[3] = { 0, 0, 0 }; // Угол поворота по умолчанию
	renderObject->GetRotationAngle(rotationAngle);
	
	float translate[3] = {0.0f, 0.0f, 0.0f}; // Позиция по умолчанию
	renderObject->GetPosition(translate);


	// Матрица SRT (масштаб-поворот-трансляция)
	bx::mtxSRT(mtx, scale[0], scale[1], scale[2], rotationAngle[0], rotationAngle[1], rotationAngle[2], translate[0], translate[1], translate[2]);
	bgfx::setTransform(mtx); // применяет матрицу

	BgfxRenderData* renderData = reinterpret_cast<BgfxRenderData*>(renderObject);

	// Обновление вершин и цветов
	auto mem = bgfx::makeRef(renderData->GetVertices(), renderData->GetVerticesSize());
	bgfx::update(renderData->GetVertexBuffer(), 0, mem);

	bgfx::setVertexBuffer(0, renderData->GetVertexBuffer());
	bgfx::setIndexBuffer(renderData->GetIndexBuffer());

	bgfx::submit(0, renderData->GetProgramHandle());
}

void RenderBackend::DrawFrame()
{
	bgfx::touch(0);
	bgfx::frame();
}
