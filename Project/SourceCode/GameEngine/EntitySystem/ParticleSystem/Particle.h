#pragma once 

struct Particle
{
	float startSize;
	float endSize;

	uint32_t startColor;
	uint32_t endColor;
};



// Particle -- ��� ��������, ������� �������� ������ ����������, ��� �������� ����(lifetime) 
// � ����� ��� ��� ����� (����, �����, �����, ���)

// Particle, LifeTime, Position, Velocity, Gravity (���������� ��� ����� ����� ���: �����, ����)
// �������� size ��� ������