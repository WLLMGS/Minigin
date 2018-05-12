#pragma once
#include <SDL.h>

class MiniginGame
{
public:
	MiniginGame();
	~MiniginGame();
	void Initialize();
	void Run();
	void Cleanup();
	virtual void LoadGameData();
protected:
	virtual void Update(float elapsedSec);
	virtual void Render();
private:
	SDL_Window* m_pWindow;
	const float m_MsPerFrame = 16.666667f;
};

