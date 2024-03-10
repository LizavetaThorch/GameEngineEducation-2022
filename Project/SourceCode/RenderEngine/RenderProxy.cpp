#include "RenderProxy.h"

void RenderProxy::SetPosition(float position[3])
{
	m_vPosition[0] = position[0];
	m_vPosition[1] = position[1];
	m_vPosition[2] = position[2];
}

void RenderProxy::SetScale(float scale[3])
{
	m_vScale[0] = scale[0];
	m_vScale[1] = scale[1];
	m_vScale[2] = scale[2];
}

void RenderProxy::SetRotationAngle(float angle[3])
{
	m_vRotation[0] = angle[0];
	m_vRotation[1] = angle[1];
	m_vRotation[2] = angle[2];
}

void RenderProxy::SetColor(int32_t color)
{
	m_vcolor = color;
}