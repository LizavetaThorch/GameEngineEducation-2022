#include "GameObject.h"

void GameObject::SetPosition(float x, float y, float z)
{
	m_vPosition[0] = x;
	m_vPosition[1] = y;
	m_vPosition[2] = z;

	m_pRenderProxy->SetPosition(m_vPosition);
}

/*
*В этом методе происходит установка позиции объекта с помощью заданных координат x, y и z. 
* Значения координат присваиваются элементам массива m_vPosition, где m_vPosition[0] соответствует координате X, 
* m_vPosition[1] - координате Y и m_vPosition[2] - координате Z.
* Далее вызывается метод SetPosition объекта m_pRenderProxy, который устанавливает позицию объекта рендеринга (m_pRenderProxy)
* на основе массива m_vPosition.
*/