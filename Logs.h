#pragma once
#include "Base.h"

class Logs : public Base
{
private:
	float m_Speed;
	void LogSetUp();
	void LogsWorldWraping();
public:
	enum class LogSize
	{
		Large,
		Medium,
		Small
	}m_LogSize;
	Logs();
	~Logs();
	void Update();
	void Draw();
	void SetLogsPos(Vector2 p_Pos);
	void SetLogsPos(float p_X,float p_Y);
	Vector2 GetLogsPos();
	void LogsMovement();
	void SetLogsSpeed(float p_Speed);
	float GetLogsSpeed();
	


};


