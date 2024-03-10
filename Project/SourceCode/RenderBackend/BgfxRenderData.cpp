#include "BgfxRenderData.h"
#include "Shaders/ShadersHelper.h"

BgfxRenderData::BgfxRenderData(
	void* vertices, UINT32 verticesSize,
	void* indices, UINT32 indicesSize,
	std::string vsShaderName, std::string psShaderName) : m_vVertices(vertices), m_vVerticesSize(verticesSize)
{
	m_Layout
		.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.end();

	m_vbh = bgfx::createDynamicVertexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(vertices, verticesSize)
		, m_Layout
	);

	// Create static index buffer for triangle list rendering.
	m_ibh = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(indices, indicesSize)
	);

	m_ProgramHandle = ShadersHelper::LoadProgram(vsShaderName.c_str(), psShaderName.c_str());
}

void BgfxRenderData::SetPosition(float position[3])
{
	m_vPosition[0] = position[0];
	m_vPosition[1] = position[1];
	m_vPosition[2] = position[2];
}


void BgfxRenderData::GetPosition(float* result)
{
	result[0] = m_vPosition[0];
	result[1] = m_vPosition[1];
	result[2] = m_vPosition[2];
}


// Scale 
void BgfxRenderData::SetScale(float scale[3])
{
	m_vScale[0] = scale[0];
	m_vScale[1] = scale[1];
	m_vScale[2] = scale[2];
}


void BgfxRenderData::GetScale(float* result)
{
	result[0] = m_vScale[0];
	result[1] = m_vScale[1];
	result[2] = m_vScale[2];
}

// Rotation
void BgfxRenderData::SetRotationAngle(float angle[3])
{
	m_vRotation[0] = angle[0];
	m_vRotation[1] = angle[1];
	m_vRotation[2] = angle[2];
}


void BgfxRenderData::GetRotationAngle(float* result)
{
	result[0] = m_vRotation[0];
	result[1] = m_vRotation[1];
	result[2] = m_vRotation[2];
}