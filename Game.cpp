#include "Game.h"
#include "SpriteSheetData.h"
#include <iostream>


Game::Game() : m_Screen(m_Screen)
{
	m_White = { 255,255,255,255 };
	m_CarStartingUnit = 880;
	m_LogsStartingUnit = 404;


	m_YUpperScreenLimit = 100;
	m_YUnit = 80;
	m_WaterYUnit = 440;

	m_TrafficSound = m_Screen.LoadSound(std::string("assets/trafficSound.wav"));
	m_CarCrashSound = m_Screen.LoadSound(std::string("assets/Carcrashsound.wav"));
	m_ScoredSound = m_Screen.LoadSound(std::string("assets/Goal.wav"));

	m_GameOver = false;
}

Game::~Game()
{
}

void Game::CarSetUp()
{
	/* just for ref
	CarStartingPos[0] = { 299,880 };
	CarStartingPos[1] = { 500, 800};
	CarStartingPos[2] = {800, 720};
	CarStartingPos[3] = {300, 640};
	CarStartingPos[4] = { 200, 560};
	*/


	for (int i = 0; i < 5; )
	{
		m_Cars[i].m_Sprite = m_Screen.LoadSprite(std::string("Assets/froggerspritesheet.png"));
		m_Cars[i].m_Sprite.scale = 0.4f;
		m_CarStartingPos[i] = { (float)(rand() % m_Screen.GetWindowWidth()),(float)m_CarStartingUnit - (m_YUnit * i) };
		m_Cars[i].SetPos(m_CarStartingPos[i]);
		i++;
	}

	m_Cars[0].m_Sprite.texture.src = SpriteSheetData::FireTruckData;
	m_Cars[1].m_Sprite.texture.src = SpriteSheetData::YellowRacingCarData;
	m_Cars[2].m_Sprite.texture.src = SpriteSheetData::GreenRacingCarData;
	m_Cars[3].m_Sprite.texture.src = SpriteSheetData::BlueRacingCarData;
	m_Cars[4].m_Sprite.texture.src = SpriteSheetData::HugeTruckData;

	m_Cars[1].SetSpeed(-3);
	m_Cars[3].SetSpeed(-6);


}

void Game::LogsSetUp()
{
	for (int i = 0; i < 5; i++)
	{
		m_LargeLogs[i].m_LogSize = Logs::LogSize::Large;
		m_LargeLogs[i].SetLogsPos((float)(rand() % m_Screen.GetWindowWidth()), (float)(m_LogsStartingUnit - (m_YUnit*0.9)*i));
	}
	m_LargeLogs[1].SetLogsSpeed(-1);
	m_LargeLogs[3].SetLogsSpeed(-1);

	for (int i = 0; i < 5; i++)
	{
		m_MediumLogs[i].m_LogSize = Logs::LogSize::Medium;
		m_MediumLogs[i].SetLogsPos((float)(m_LargeLogs[i].GetLogsPos().x + m_LargeLogs[i].m_Sprite.texture.src.w + 100), (float)(m_LargeLogs[i].GetLogsPos().y));
	}
	m_MediumLogs[1].SetLogsSpeed(-1);
	m_MediumLogs[3].SetLogsSpeed(-1);




}

void Game::GoalReactionSetUp()
{
	for (int i = 0; i < 5; i++)
	{
		m_Froggy[i].m_Sprite.position = m_Gui.m_Goal[i].position;
		m_Froggy[i].m_Sprite.scale = m_Gui.m_Goal[i].scale;
	}
}

void Game::FrogWorldWrapping()
{
	if (m_Player.m_Sprite.position.x > m_Screen.GetWindowWidth())
	{
		m_Gui.MinusLives();
		m_Player.Respawn();
	}
	else if (m_Player.m_Sprite.position.x < 0)
	{
		m_Gui.MinusLives();
		m_Player.Respawn();
	}
}


void Game::Update()
{
	ResetGame();
	m_Gui.Update(); // check Clicking Start Button
	if (!m_GameOver)
	{
		m_Player.Update();
		FrogWorldWrapping();
		for (int i = 0; i < 5; i++)
		{
			m_Cars[i].Update();
			m_LargeLogs[i].Update();
		}
		for (int i = 0; i < 5; i++)
		{
			m_MediumLogs[i].Update();
		}
		GameLogic();
		CheckGameOver();
	}
}

void Game::Draw()
{

	// gameBackground
	m_Gui.Draw(m_Gui.GetGameScene());

	if (!m_GameOver)
	{
		//Gameplay Screen
		if (m_Gui.GetGameScene() == GUI::GameState::Gameplay) 
		{
			m_Screen.PlaySound(m_TrafficSound);
			m_Gui.Draw(GUI::GameState::Gameplay); 
			for (int i = 0; i < 5; i++)
			{
				m_LargeLogs[i].Draw();
				m_Cars[i].Draw();
				m_Froggy[i].Draw();
			}
			for (int i = 0; i < 5; i++)
			{
				m_MediumLogs[i].Draw();
			}
			m_Player.Draw(); // Frog
		}
	}
}

bool Game::AABBCollisionCheck(Frog p_player, Sprite p_rhs)
{
	if (p_player.m_CollisionBox.x < p_rhs.position.x + (p_rhs.texture.src.w * p_rhs.scale)
		&& p_player.m_CollisionBox.x + p_player.m_CollisionBoxW > p_rhs.position.x
		&& p_player.m_CollisionBox.y  < p_rhs.position.y + (p_rhs.texture.src.h * p_rhs.scale)
		&& p_player.m_CollisionBox.y + p_player.m_CollisionBoxH > p_rhs.position.y)
		return true;
	else
		return false;
}

bool Game::PixelCollisionCheck(Vector2 p_lhs, Sprite p_rhs)
{
	if (p_lhs.x > p_rhs.position.x && p_lhs.x < p_rhs.position.x + (p_rhs.texture.src.w * p_rhs.scale)
		&& p_lhs.y > p_rhs.position.y && p_lhs.y < p_rhs.position.y + (p_rhs.texture.src.h * p_rhs.scale ))
		return true;
	else
		return false;
}

void Game::GameLogic()
{
	
	for (int i = 0; i < 5; i++)
	{
		if (AABBCollisionCheck(m_Player, m_Cars[i].m_Sprite) && m_Player.m_dir == Frog::m_Movement::stop)
		{
			m_Screen.PlaySound(m_CarCrashSound);
			m_Gui.MinusLives();
			m_Player.Respawn();
		}
	}

	if (m_Player.m_Sprite.position.y < m_WaterYUnit && m_Player.m_dir == Frog::m_Movement::stop)
	{
		for (int i = 0; i < 5; i++)
		{
			if (AABBCollisionCheck(m_Player, m_LargeLogs[i].m_Sprite) && m_Player.m_dir == Frog::m_Movement::stop)
			{
				m_Player.m_Sprite.position.x += m_LargeLogs[i].GetLogsSpeed();
				return;
			}
			else if (AABBCollisionCheck(m_Player, m_MediumLogs[i].m_Sprite) && m_Player.m_dir == Frog::m_Movement::stop)
			{
				m_Player.m_Sprite.position.x += m_MediumLogs[i].GetLogsSpeed();
				return;
			}
			else if (AABBCollisionCheck(m_Player, m_Gui.m_Goal[i]) && m_Player.m_dir == Frog::m_Movement::stop)
			{
				m_Screen.PlaySound(m_ScoredSound);
				m_Gui.AddScore();
				m_Froggy[i].SetScoringFrogAlive(true);
				m_Player.Respawn();
				return;
			}
		}
		m_Gui.MinusLives();
		m_Player.Respawn();
		return;
		
	}
}

void Game::ResetGame()
{
	if (m_Gui.GetGameScene() == GUI::GameState::Victory || m_Gui.GetGameScene() == GUI::GameState::Lose)
	{
		if (m_Screen.IsKeyDown(Key::Space))
		{
			m_Gui.SetGameScene(GUI::GameState::StartMenu);
			m_GameOver = false;
			m_Gui.ResetGui();
			for (int i = 0; i < 5; i++)
			{
				m_Froggy[i].ResetFroggy();
			}
		}
	}
}


void Game::CheckGameOver()
{
	if (m_Gui.GetLives() == 0)
	{
		m_GameOver = true;
		m_Gui.SetGameScene(GUI::GameState::Lose);
		m_Screen.StopSound(m_TrafficSound);
		return;
	}
	if (m_Gui.GetTime() == 0)
	{
		m_GameOver = true;
		m_Gui.SetGameScene(GUI::GameState::Lose);
		m_Screen.StopSound(m_TrafficSound);
		return;
	}
	for (int i = 0; i < 5; i++)
	{
		if (m_Froggy[i].GetScoringFrogAlive() == false)
		{
			return;
		}
	}
	m_Screen.StopSound(m_TrafficSound);
	m_Gui.SetGameScene(GUI::GameState::Victory);
	m_GameOver = true;
}

void Game::GameSetUp()
{
	CarSetUp();
	LogsSetUp();
	GoalReactionSetUp();
}




