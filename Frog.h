#pragma once
#include "Base.h"
#include "GUI.h"
#include "Screen.h"

class Frog : public Base
{
private:
	void FrogAnimation();
	bool m_IsMoving;
	int m_MiliSec, m_MiliInterval;

	int m_XspritesheetBox;
	int m_YspritesheetBox;
	int m_AnimationEndingBox, m_WaterYaxis,m_FrogUnitOnGround,m_FrogUnitOnWater,m_FrameNeededForAnimation, m_YaxisLimitation;

	Sound m_FrogDyingSound;

	int m_MovingPixel;

	Color White{ 255,255,255,255 };
	GUI m_Gui;

	void timer();
	void FrogControl();
	void DrawCollisionBox();
public:
	
	Frog();
	~Frog();

	void Update();
	void Draw();
	void CollisionBoxUpdate();
	void Respawn();
	enum class m_Movement
	{
		Up,
		Left,
		Right,
		Down,
		stop

	}m_dir;

	Vector2 m_CollisionBox;
	float m_CollisionBoxW,m_CollisionBoxH;
};


