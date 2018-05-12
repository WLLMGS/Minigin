#include "MiniginPCH.h"
#include "Logger.h"
#include "TextComponent.h"
#include <algorithm>
#include <ctime>


Logger::~Logger()
{
	for(auto gameObject : m_pMessages)
	{
		delete gameObject;
		gameObject = nullptr;
	}
}

void Logger::Log(string message)
{
	//scroll up
	MoveObjects();
	//add new object
	
	//time
	time_t now = time(0);

	char str[26];
	ctime_s(str, sizeof(str), &now);

	string log = string(str) + ": " + message;

	auto gameObject = new dae::GameObject();
	auto text = new TextComponent(dae::DEFAULT, { 255,0,0,1 }, log);
	gameObject->AddComponent(text);
	gameObject->Transform()->Translate(m_StartX, m_StartY, 1);

	m_pMessages.push_back(gameObject);
}

void Logger::Render()
{
	for (auto gameObject : m_pMessages) gameObject->RootRender();
}



void Logger::MoveObjects()
{
	vector<size_t> toRemove;

	for(size_t t{}; t < m_pMessages.size(); ++t)
	{
		if(m_pMessages[t]->Transform()->GetPosition().y < 0.0f)
		{
			toRemove.push_back(t);
		}
		else
		{
			m_pMessages[t]->Translate(0, m_Offset, 1);
		}
	}

	for(auto t : toRemove)
	{
		dae::GameObject* obj = m_pMessages[t];
		m_pMessages.erase(std::remove(m_pMessages.begin(), m_pMessages.end(), obj), m_pMessages.end());
		delete obj;
		obj = nullptr;
	}
}

