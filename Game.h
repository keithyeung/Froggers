#pragma once
#include "Screen.h"
#include "GUI.h"
#include "Frog.h"
#include "Car.h"
#include "ScoredFrog.h"
#include "Logs.h"


class Game
{
private:
	
	GUI m_Gui;
	
	Frog m_Player;
	ScoredFrog m_Froggy[5];

	Car m_Cars[5];
	Vector2 m_CarStartingPos[5];

	Logs m_LargeLogs[5];
	Logs m_MediumLogs[10];

	Screen& m_Screen;
	Color m_White;
	
	bool  m_GameOver;
	int m_YUpperScreenLimit, m_YUnit,m_WaterYUnit;
	float m_CarStartingUnit, m_LogsStartingUnit;
	bool AABBCollisionCheck(Frog p_Player,Sprite p_rhs);
	bool PixelCollisionCheck(Vector2 p_lhs, Sprite p_rhs);
	void GameLogic();
	void ResetGame();
	void CarSetUp();
	void LogsSetUp();
	void GoalReactionSetUp();
	void FrogWorldWrapping();

	Sound m_CarCrashSound, m_TrafficSound, m_ScoredSound;

public:
	Game();
	~Game();
	

	void GameSetUp();
	void Update();
	void Draw();
	void CheckGameOver();

};

