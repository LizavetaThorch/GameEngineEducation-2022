#pragma once //��������� ����������� ���� � ��� �� ��� ������
#include "Common.h"


class SCRIPTSYSTEM_API IScriptProxy
{
public:
	// �������� ����� �� ����� Lua
	virtual float UpdateMovements(bool left, bool right, float deltaVel, float spd) = 0;
};