#pragma once
#include "Scene.h"

class PacmanDemoScene : public dae::Scene
{
public:
	enum GameMode
	{
		Singleplayer = 0,
		MultiplayerGhost = 1,
		MultiplayerMsPacman = 2
	};
public:
	PacmanDemoScene(GameMode mode = Singleplayer);
	~PacmanDemoScene();
	virtual void Update(float elapsedSec) override;
	virtual void Render();
	void Reset();


private:
	dae::GameObject* m_pPacman = nullptr;
	GameMode m_Mode;
	void Init();
};

