#pragma once
#include "TextObject.h"
#include "Singleton.h"

class Logger final : public dae::Singleton<Logger>
{
public:
	~Logger();
	void Log(string message);
	void Render();

	Logger() = default;
private:
	void MoveObjects();
private:
	vector<dae::GameObject*> m_pMessages;
	const float m_StartX = 10.0f;
	const float m_StartY = 50.0f;
	const float m_Offset = -GameSettings::FontSize;
};

