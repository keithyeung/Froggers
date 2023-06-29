#include "Car.h"
#include <cstdlib>

void Car::Movement()
{
	m_CarPos.x += m_Speed;
	m_Sprite.position = m_CarPos;
}

Car::Car() : Base()
{
	m_Speed = 3;
}

Car::~Car()
{
}

void Car::Draw()
{
	m_Screen.DrawSprite(m_Sprite);
}

void Car::Update()
{
	Movement();
	WorldWrapping();
}

void Car::WorldWrapping()
{
	if (m_CarPos.x >= m_Screen.GetWindowWidth() + m_Sprite.texture.src.w && m_Speed > 0)
		m_CarPos.x = (float)(0 - m_Sprite.texture.src.w);
	else if (m_CarPos.x <= 0 - m_Sprite.texture.src.x && m_Speed < 0)
		m_CarPos.x = (float)(m_Screen.GetWindowWidth() + m_Sprite.texture.src.w);
}

void Car::SetPos(Vector2 p_pos)
{
	m_CarPos = p_pos;
}

void Car::SetSpeed(float p_speed)
{
	m_Speed *= p_speed;
}

Vector2 Car::GetPos()
{
	return m_CarPos;
}

float Car::GetSpeed()
{
	return m_Speed;
}

