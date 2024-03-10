#pragma once

#include "Common.h"

class RENDERENGINE_API RenderProxy
{
public:
	RenderProxy() = default;

	void GetPosition(float* result)
	{
		result[0] = m_vPosition[0];
		result[1] = m_vPosition[1];
		result[2] = m_vPosition[2];
	}
	void SetPosition(float position[3]);

	float m_vPosition[3];

	// Обновление Масштаба
	void GetScale(float* result)
	{
		result[0] = m_vScale[0];
		result[1] = m_vScale[1];
		result[2] = m_vScale[2];
	}

	void SetScale(float scale[3]);

	float m_vScale[3];

	// Обновление Угла поворота
	void GetRotationAngle(float* result)
	{
		result[0] = m_vRotation[0];
		result[1] = m_vRotation[1];
		result[2] = m_vRotation[2];
	}
	void SetRotationAngle(float angle[3]);

	float m_vRotation[3];

	// Обновление Цвета
	uint32_t GetColor()
	{
		return m_vcolor;
	}
	void SetColor(int32_t color);

	uint32_t m_vcolor;
};
