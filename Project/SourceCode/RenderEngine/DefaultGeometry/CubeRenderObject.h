#pragma once

#include "../RenderObject.h"

namespace
{
	struct PosColorVertex
	{
		float x;
		float y;
		float z;
		uint32_t abgr;
	};
};

class RENDERENGINE_API CubeRenderObject final : public RenderObject
{
public:
	CubeRenderObject(RenderProxy* pRenderProxy);

	virtual void* GetVertices() const override { return (void*)s_cubeVertices; }
	virtual UINT32 GetVerticesSize() const override { return sizeof(s_cubeVertices); }
	virtual void* GetIndices() const override { return (void*)s_cubeTriList; }
	virtual UINT32 GetIndicesSize() const override { return sizeof(s_cubeTriList); }
	virtual std::string GetVsShaderName() const override { return "vs_cubes"; }
	virtual std::string GetPsShaderName() const override { return "fs_cubes"; }
	virtual void SyncObjectWithProxy() override;

private:
	PosColorVertex s_cubeVertices[8];

	inline static const uint16_t s_cubeTriList[] =
	{
		0, 1, 2, // 0
		1, 3, 2,
		4, 6, 5, // 2
		5, 6, 7,
		0, 2, 4, // 4
		4, 2, 6,
		1, 5, 3, // 6
		5, 7, 3,
		0, 4, 1, // 8
		4, 5, 1,
		2, 3, 6, // 10
		6, 3, 7,
	};
};

