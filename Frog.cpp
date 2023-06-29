#include "Frog.h"



Frog::Frog() : Base()
{
	m_srcW = 90;
	m_srcH = 120;

	m_startPos.x = 500;
	m_startPos.y = (float)(m_Screen.GetWindowHeight() - m_srcH/4);

	m_XspritesheetBox = 95;
	m_AnimationEndingBox = 600;
	m_WaterYaxis = 560;
	m_FrogUnitOnGround = 80;
	m_FrogUnitOnWater = 75;
	m_YaxisLimitation = m_startPos.y - 50;
	m_FrameNeededForAnimation = 6;

	m_Sprite = m_Screen.LoadSprite(std::string("Assets/FroggerSpriteSheet.png"));
	m_Sprite.texture.src = { 30,0,m_srcW,m_srcH };
	m_Sprite.position = m_startPos;
	m_Sprite.origin = { (float)m_srcW/2,(float)m_srcH/2 +30};
	m_Sprite.angle = 180;

	m_CollisionBox.x = m_Sprite.position.x - m_Sprite.texture.src.w / 2;
	m_CollisionBox.y = m_Sprite.position.y;
	m_CollisionBoxW = (float)(m_Sprite.texture.src.w / 1.5f);
	m_CollisionBoxH = (float)(m_Sprite.texture.src.h/2);

	m_Sound = m_Screen.LoadSound(std::string("Assets/FrogSound.wav"));
	m_FrogDyingSound = m_Screen.LoadSound(std::string("Assets/FrogDying.wav"));

	m_MiliSec = 0;
	m_MiliInterval = 10;
	m_IsMoving = false;
}

Frog::~Frog()
{

}

void Frog::Update() 
{
	if (!m_IsMoving)
	{
		FrogControl();
	}
	else if (m_IsMoving)
	{
		timer();
	}
	if (m_Sprite.position.y > m_WaterYaxis)
	{
		
		m_MovingPixel = m_FrogUnitOnGround/ m_FrameNeededForAnimation;
	}
	else if (m_Sprite.position.y < m_WaterYaxis)
	{
		m_MovingPixel = m_FrogUnitOnWater / m_FrameNeededForAnimation;
	}
	CollisionBoxUpdate();
	FrogAnimation();
}

void Frog::Draw()
{
	m_Screen.DrawSprite(m_Sprite);
}

void Frog::FrogControl()
{
	if (m_Screen.IsKeyDown(Key::Right))
	{
		m_Screen.PlaySound(m_Sound);
		m_dir = m_Movement::Right;
	}
	else if (m_Screen.IsKeyDown(Key::Left))
	{
		m_Screen.PlaySound(m_Sound);
		m_dir = m_Movement::Left;
	}
	else if (m_Screen.IsKeyDown(Key::Up))
	{
		m_Screen.PlaySound(m_Sound);
		m_dir = m_Movement::Up;
	}
	else if (m_Screen.IsKeyDown(Key::Down) && m_Sprite.position.y < m_YaxisLimitation)
	{
		m_Screen.PlaySound(m_Sound);
		m_dir = m_Movement::Down;
	}
}

void Frog::timer()
{
	if (m_MiliSec < 10)
	{
		m_MiliSec++;
	}
	else if (m_MiliSec == 10)
	{
		m_MiliSec = 0;
		m_IsMoving = false;
		m_Screen.StopSound(m_Sound);
	}
}

void Frog::CollisionBoxUpdate()
{
	m_CollisionBox.x = m_Sprite.position.x - m_Sprite.texture.src.w / 3;
	m_CollisionBox.y = m_Sprite.position.y - m_Sprite.texture.src.h / 4;
}



void Frog::Respawn()
{
	m_Screen.PlaySound(m_FrogDyingSound);
	m_Sprite.position = m_startPos;
}

void Frog::DrawCollisionBox()
{
	m_Screen.DrawRectangle((int)m_CollisionBox.x, (int)m_CollisionBox.y, (int)m_CollisionBoxW, (int)m_CollisionBoxH, White);
}

void Frog::FrogAnimation()
{
	if (m_dir == m_Movement::Up)
	{
		if (m_Sprite.texture.src.x == m_AnimationEndingBox)
		{
			m_Sprite.texture.src = { 30,0,m_srcW,m_srcH };
			m_IsMoving = true;
			m_dir = m_Movement::stop;
		}
		else
		{
			m_Sprite.angle = 180;
			m_Sprite.texture.src.x += m_XspritesheetBox;
			m_Sprite.position.y -= m_MovingPixel;
		}
	}
	if (m_dir == m_Movement::Right)
	{
		if (m_Sprite.texture.src.x == m_AnimationEndingBox)
		{
			m_Sprite.texture.src = { 30,0,m_srcW,m_srcH };
			m_IsMoving = true;
			m_dir = m_Movement::stop;
		}
		else
		{
			m_Sprite.angle = 270;
			m_Sprite.texture.src.x += m_XspritesheetBox;
			m_Sprite.position.x += m_MovingPixel;
		}
	}
	if (m_dir == m_Movement::Left)
	{
		if (m_Sprite.texture.src.x == m_AnimationEndingBox)
		{
			m_Sprite.texture.src = { 30,0,m_srcW,m_srcH };
			m_IsMoving = true;
			m_dir = m_Movement::stop;
		}
		else
		{
			m_Sprite.angle = 90;
			m_Sprite.texture.src.x += m_XspritesheetBox;
			m_Sprite.position.x -= m_MovingPixel;
		}
	}
	if (m_dir == m_Movement::Down)
	{
		if (m_Sprite.texture.src.x == m_AnimationEndingBox)
		{
			m_Sprite.texture.src = { 30,0,m_srcW,m_srcH };
			m_IsMoving = true;
			m_dir = m_Movement::stop;
		}
		else
		{
			m_Sprite.angle = 0;
			m_Sprite.texture.src.x += m_XspritesheetBox;
			m_Sprite.position.y += m_MovingPixel;
		}
	}
}
