#pragma once
#include "Screen.h"
#include "Base.h"
#include <Vector>

class GUI : public Base
{
private:
	//start
	Sprite m_StartMenuBackground, m_StartButton,m_Instructions;
	//gameplay
	Sprite m_GameBackground;

	//Victory Scene
	Sprite m_VictoryBackground;
	Sound m_VictorySound;
	Vector2 m_WinningTextPos;

	//Lose Scene
	Sprite m_LoseBackground;
	Sound m_LoseSound;
	Vector2 m_LosingTextPos;


	Screen& m_Screen;

	Sprite m_LivesSprite;
	float m_Lives;
	int m_Score,m_Sec, m_MiliSec;
	Color White{ 255,255,255,255 };
	int CalculateEndingScore();
	void Timer();
	void IsStartButtonClicked();

public:
	GUI();
	~GUI();


	Sprite m_Goal[5];

	enum class GameState { StartMenu, Gameplay, Victory, Lose }m_GameScene;
	void SetGameScene(GameState p_gameState);
	GameState GetGameScene();

	void Update();
	void Draw(GameState p_gameState);
	void MinusLives();
	void AddScore();
	void SetTime(int time);
	float GetLives();
	int GetScore();
	int GetTime();
	void ResetGui();
	

};




