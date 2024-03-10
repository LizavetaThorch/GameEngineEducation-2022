#pragma once

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include "IRenderData.h"

class RenderObject;

class RENDERBACKEND_API BgfxRenderData final : public IRenderData
{
public:
	BgfxRenderData(
		void* vertices, UINT32 verticesSize,
		void* indices, UINT32 indicesSize,
		std::string vsShaderName, std::string psShaderName);

	bgfx::DynamicVertexBufferHandle GetVertexBuffer() { return m_vbh; }
	bgfx::IndexBufferHandle GetIndexBuffer() { return m_ibh; }
	bgfx::ProgramHandle GetProgramHandle() { return m_ProgramHandle; }
	void* GetVertices() { return m_vVertices; }
	UINT32 GetVerticesSize() { return m_vVerticesSize; }
	virtual void GetPosition(float* result) override;
	virtual void SetPosition(float position[3]) override;
	// добавлены размер и поворот
	virtual void GetScale(float* result) override;
	virtual void SetScale(float scale[3]) override;
	virtual void GetRotationAngle(float* result)override;
	virtual void SetRotationAngle(float rotationAngles[3]) override;

private:
	bgfx::VertexLayout m_Layout = bgfx::VertexLayout();
	bgfx::DynamicVertexBufferHandle m_vbh = bgfx::DynamicVertexBufferHandle();
	bgfx::IndexBufferHandle m_ibh = bgfx::IndexBufferHandle();
	bgfx::ProgramHandle m_ProgramHandle = bgfx::ProgramHandle();

	float m_vPosition[3];
	float m_vScale[3];
	float m_vRotation[3];
	void* m_vVertices;
	UINT32 m_vVerticesSize;
};

