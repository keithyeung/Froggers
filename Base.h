#pragma once
#include "screen.h"

class Base 
{
private:
	int miliSec;
public:
	int m_srcW, m_srcH;
	Vector2 m_startPos;

	Sprite m_Sprite;
	Sound m_Sound;
	Screen &m_Screen;
	Base();
	~Base();
	virtual void Update();
	virtual void Draw();
};
