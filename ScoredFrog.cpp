#include "ScoredFrog.h"

ScoredFrog::ScoredFrog()
{
	m_Alive = false;
	for (int i = 0; i < 5; i++)
	{
		m_Sprite = m_Screen.LoadSprite(std::string("Assets/Froggerspritesheet.png"));
		m_Sprite.texture.src = { 32,50,85, 68 };
	}
}

ScoredFrog::~ScoredFrog()
{
}

void ScoredFrog::SetScoringFrogAlive(bool TorF)
{
	m_Alive = TorF;
}

bool ScoredFrog::GetScoringFrogAlive()
{
	return m_Alive;
}

void ScoredFrog::Draw()
{
	if (m_Alive)
	{
		m_Screen.DrawSprite(m_Sprite);
	}
}

void ScoredFrog::ResetFroggy()
{
	m_Alive = false;
}
