#pragma once

#include "Common.h"

class RENDERBACKEND_API IRenderData
{
public:
	virtual void GetPosition(float* result) = 0;
	virtual void SetPosition(float position[3]) = 0;

	virtual void GetScale(float* result) = 0;
	virtual void SetScale(float scale[3]) = 0;

	virtual void GetRotationAngle(float*  result) = 0;
	virtual void SetRotationAngle(float angle[3]) = 0;
	// добавлены размер и поворот
};
