#include "Logs.h"

void Logs::LogSetUp()
{
	switch (m_LogSize)
	{
	case(LogSize::Large):
		m_Sprite.texture.src = { 54,460, 586, 100 };
		break;
	case(LogSize::Medium):
		m_Sprite.texture.src = {54,583,452,100};
		break;
	case(LogSize::Small):
		m_Sprite.texture.src = {672,460,308,100};
		break;
	}
}

void Logs::LogsWorldWraping()
{
	if (m_Sprite.position.x >= m_Screen.GetWindowWidth() + m_Screen.GetWindowWidth() / 2 && m_Speed > 0)
	{
		m_Sprite.position.x = (float)(0 - m_Screen.GetWindowWidth() / 2);
	}
	else if (m_Sprite.position.x <= 0 - m_Screen.GetWindowWidth() / 2 && m_Speed < 0)
	{
		m_Sprite.position.x = (float)(m_Screen.GetWindowWidth() + m_Screen.GetWindowWidth() / 2);
	}
}

Logs::Logs() 
{
	m_Sprite = m_Screen.LoadSprite(std::string("assets/FroggerSpriteSheet.png"));
	m_Sprite.scale = 0.5f;
	m_Speed = 5;
}

Logs::~Logs()
{
}

void Logs::Update()
{
	LogSetUp();
	LogsMovement();
	LogsWorldWraping();
}

void Logs::Draw()
{
	m_Screen.DrawSprite(m_Sprite);
}

void Logs::SetLogsPos(Vector2 p_Pos)
{
	m_Sprite.position = p_Pos;
}

void Logs::SetLogsPos(float p_X, float p_Y)
{
	m_Sprite.position.x = p_X;
	m_Sprite.position.y = p_Y;
}

Vector2 Logs::GetLogsPos()
{
	return m_Sprite.position;
}

void Logs::LogsMovement()
{
	m_Sprite.position.x += m_Speed;
}

void Logs::SetLogsSpeed(float p_Speed)
{
	m_Speed *= p_Speed;
}

float Logs::GetLogsSpeed()
{
	return m_Speed;
}
