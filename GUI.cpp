#include "GUI.h"
//#include "SpriteSheetData.h"
#include <iostream>


GUI::GUI() : m_Screen(m_Screen)
{
	//default scene
	m_GameScene = GUI::GameState::StartMenu;
	//startMenu
	m_StartMenuBackground = m_Screen.LoadSprite(std::string("Assets/FroggerStartMenuBackground.png"));

	m_StartButton = m_Screen.LoadSprite(std::string("Assets/StartButton.png"));
	m_StartButton.position = { 250,600 };
	
	//GamePlay
	m_GameBackground = m_Screen.LoadSprite(std::string("Assets/Froggerbackground.png"));
	m_LivesSprite = m_Screen.LoadSprite(std::string("Assets/PepetheFrog.png"));
	m_LivesSprite.scale = 0.1f;

	for (int i = 0; i < 5; i++)
	{
		m_Goal[i] = m_Screen.LoadSprite(std::string("Assets/Froggerspritesheet.png"));
		m_Goal[i].texture.src = { 40,300, 104, 100 };
		m_Goal[i].position = { (float)(55 + (205 * i)),35 };
		m_Goal[i].scale = 0.75f;
	}
	m_Score = 0;
	m_Lives = 7;
	m_Sec = 90;
	m_MiliSec = 0;

	//Victory Scene
	m_VictoryBackground = m_Screen.LoadSprite(std::string("Assets/FroggerVictoryScene.png"));
	m_VictorySound = m_Screen.LoadSound(std::string("Assets/ApexWinningSound.wav"));
	m_WinningTextPos = { (float)(m_Screen.GetWindowWidth() / 2), (float)(m_Screen.GetWindowHeight() * 0.8) };

	//Lose Scene
	m_LoseBackground = m_Screen.LoadSprite(std::string("Assets/LosingScene.png"));
	m_LoseSound = m_Screen.LoadSound(std::string("Assets/FailingQuote.wav"));
	m_LosingTextPos = { (float)(m_Screen.GetWindowWidth() / 3),(float)(m_Screen.GetWindowHeight() * 0.8) };



}

GUI::~GUI()
{
}

void GUI::SetGameScene(GameState p_gameState)
{
	m_GameScene = p_gameState;
}

GUI::GameState GUI::GetGameScene()
{
	return m_GameScene;
}

void GUI::IsStartButtonClicked()
{
	if (m_Screen.GetMouseX() >= m_StartButton.position.x && m_Screen.GetMouseX() <= (m_StartButton.position.x + m_StartButton.texture.width)
		&& m_Screen.GetMouseY() >= m_StartButton.position.y && m_Screen.GetMouseY() <= (m_StartButton.position.y+m_StartButton.texture.height)
		&& m_Screen.IsButtonDown(Button::Left))
	{
		m_GameScene = GameState::Gameplay;
	}
}

void GUI::Update()
{
	IsStartButtonClicked();
	if (m_GameScene == GameState::Gameplay)
	{
		Timer();
	}
}

void GUI::Draw(GameState p_gameState)
{
	if (p_gameState == GameState::StartMenu)
	{
		m_Screen.DrawSprite(m_StartMenuBackground);
		m_Screen.DrawSprite(m_StartButton);
	}
	else if (p_gameState == GameState::Gameplay)
	{
		m_Screen.DrawSprite(m_GameBackground);
		for (int i = 0; i < 5; i++)
		{
			m_Screen.DrawSprite(m_Goal[i]);
		}
		m_Screen.DrawText(0, 0, White, std::string("Score: " + std::to_string(this->GetScore())));
		m_Screen.DrawText(m_Screen.GetWindowWidth()/2, 0, White, std::string("Time: " + std::to_string(this->GetTime())));
		for (int i = 0; i < m_Lives; i++)
		{
			m_LivesSprite.position = { (0 + (i * m_LivesSprite.texture.src.w * m_LivesSprite.scale)),(float)(m_Screen.GetWindowHeight() - m_LivesSprite.texture.src.h * m_LivesSprite.scale) };
			m_Screen.DrawSprite(m_LivesSprite);
		}
	}
	else if (p_gameState == GameState::Victory)
	{
		m_Screen.DrawSprite(m_VictoryBackground);
		m_Screen.PlaySound(m_VictorySound);
		m_Screen.DrawText((int)m_WinningTextPos.x, (int)m_WinningTextPos.y, White, std::string("Your Score is : "+ std::to_string(CalculateEndingScore())));
		m_Screen.DrawText((int)m_WinningTextPos.x, (int)(m_WinningTextPos.y + 100), White, std::string("---Press SPACE to restart---"));
		m_Screen.DrawText((int)m_WinningTextPos.x, (int)(m_WinningTextPos.y + 50), White, std::string(" Score = Score + (Time * 100)"));
	}
	else if (p_gameState == GameState::Lose)
	{
		m_Screen.DrawSprite(m_LoseBackground);
		m_Screen.PlaySound(m_LoseSound);
		m_Screen.DrawText((int)m_LosingTextPos.x, (int)m_LosingTextPos.y, White, std::string("Your Score is : " + std::to_string(GetScore())));
		m_Screen.DrawText((int)m_LosingTextPos.x, (int)m_LosingTextPos.y + 50, White, std::string("---Press SPACE to try again---"));
	}
}

void GUI::MinusLives()
{
	m_Lives--;
}

void GUI::AddScore()
{
	m_Score += 500;
}

void GUI::SetTime(int time)
{
	m_Sec = time;
}

float GUI::GetLives()
{
	return m_Lives;
}

int GUI::GetScore()
{
	return m_Score;
}

int GUI::GetTime()
{
	return m_Sec;
}

void GUI::ResetGui()
{
	m_GameScene = GameState::StartMenu;
	m_Sec = 90;
	m_Lives = 7;
	m_Score = 0;
}

int GUI::CalculateEndingScore()
{
	return m_Score + (m_Sec * 100);
}

void GUI::Timer()
{
	if (m_MiliSec < 60)
		m_MiliSec++;
	else if (m_MiliSec == 60)
	{
		m_Sec--;
		m_MiliSec = 0;
	}
}

