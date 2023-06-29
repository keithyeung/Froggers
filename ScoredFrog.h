#pragma once
#include"Base.h"

class ScoredFrog : public Base
{
private:
	bool m_Alive;
	
public:

	ScoredFrog();
	~ScoredFrog();
	void SetScoringFrogAlive(bool TorF);
	bool GetScoringFrogAlive();
	void Draw();
	void ResetFroggy();
};

