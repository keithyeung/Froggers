#pragma once
#include "Base.h"


class Car : public Base
{
private:
	Vector2 m_CarPos;
	float m_Speed;

	void Movement();
public:
	Car();
	~Car();
	void Draw();
	void Update();
	void WorldWrapping();
	void SetPos(Vector2 p_pos);
	void SetSpeed(float p_speed);

	Vector2 GetPos();
	float GetSpeed();
};

