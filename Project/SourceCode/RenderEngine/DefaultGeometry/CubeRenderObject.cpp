#include "CubeRenderObject.h"

CubeRenderObject::CubeRenderObject(RenderProxy* pRenderProxy) :
	RenderObject(pRenderProxy), 
	s_cubeVertices{
		{-1.0f,  1.0f,  1.0f, pRenderProxy->GetColor()},
		{ 1.0f,  1.0f,  1.0f, pRenderProxy->GetColor() },
		{-1.0f, -1.0f,  1.0f, pRenderProxy->GetColor() },
		{ 1.0f, -1.0f,  1.0f, pRenderProxy->GetColor() },
		{-1.0f,  1.0f, -1.0f, pRenderProxy->GetColor() },
		{ 1.0f,  1.0f, -1.0f, pRenderProxy->GetColor() },
		{-1.0f, -1.0f, -1.0f, pRenderProxy->GetColor() },
		{ 1.0f, -1.0f, -1.0f, pRenderProxy->GetColor() },
	}
{

}

void CubeRenderObject::SyncObjectWithProxy() 
{
	for (int i = 0; i < 8; ++i) {
		s_cubeVertices[i].abgr = m_pRenderProxy->GetColor();
	}
}