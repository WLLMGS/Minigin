#include "MiniginPCH.h"
#include "EngineTestScene.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "PacmanPrefab.h"
#include "LevelLoader.h"
#include "ColliderComponent.h"


EngineTestScene::EngineTestScene() :
Scene("Engine Test Scene")
{
	//fps counter
	auto textObj = new dae::GameObject();
	m_pFpsComp = new TextComponent(dae::FontName::DEFAULT, { 255,125,125 }, "FPS: ");
	textObj->AddComponent(m_pFpsComp);
	textObj->Translate(10.0f, 10.0f, 1);
	AddChild(textObj);

	dae::LevelLoader::LoadLevel("level01", this);

	//pacman
	m_pTestObject = new PacmanPrefab();
	m_pTestObject->Translate(20, 100, 1);
	AddChild(m_pTestObject);

}

EngineTestScene::~EngineTestScene() = default;



void EngineTestScene::Update(float elapsedSec)
{
	m_FpsTimer += elapsedSec;
	++m_FpsCounter;

	if((m_FpsTimer) >= 1.0f)
	{	
		string message = "X: " + to_string(m_pTestObject->Transform()->GetPosition().x) + " Y: " + to_string(m_pTestObject->Transform()->GetPosition().y);
		//Logger::GetInstance().Log(message);
		m_pFpsComp->SetText("FPS: " + to_string(m_FpsCounter));
		m_FpsCounter = 0;
		m_FpsTimer = 0.0f;
	}

	
	//update input
	auto command = dae::InputManager::GetInstance().HandleInput();

	if (command) command->Execute(m_pTestObject);

	for(auto obj : m_pGameObjects)
	{
		if(obj != m_pTestObject && obj->GetComponent<ColliderComponent>())
		{
			if(!obj->GetComponent<ColliderComponent>()->IsDynamic())
			{
				//only check collision with static objects (for now)
				m_pTestObject->GetComponent<ColliderComponent>()->CheckCollision(obj->GetComponent<ColliderComponent>());
			}
		}
	}
	
}

