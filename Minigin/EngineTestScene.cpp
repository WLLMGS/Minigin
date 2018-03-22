#include "MiniginPCH.h"
#include "EngineTestScene.h"
#include "ResourceManager.h"
#include "BaseComponent.h"

#include "SpriteComponent.h"

#include "InputManager.h"


EngineTestScene::EngineTestScene() :
Scene("Engine Test Scene")
{
	//add game objects
	auto font = dae::ResourceManager::GetInstance().RequestFont(dae::FontName::DEFAULT);
	m_pTxtFpsCounter = new dae::TextObject("FPS: ", font);
	m_pTxtFpsCounter->SetPosition(10, 10);

	AddChild(m_pTxtFpsCounter);

	m_pTestObject = new GameActor();
	m_pTestObject->AddComponent(new dae::SpriteComponent(dae::TextureName::PACMAN));
	m_pTestObject->Translate(10, 200, 1);
	m_pTestObject->Transform()->SetScale(2, 2, 2);
	m_pTestObject->Transform()->SetRotation(0.0f);

	AddChild(m_pTestObject);
}

EngineTestScene::~EngineTestScene() = default;



void EngineTestScene::Update(float elapsedSec)
{
	m_FpsTimer += elapsedSec;
	++m_FpsCounter;

	if((m_FpsTimer / 1000.0f) >= 1.0f)
	{
		m_pTxtFpsCounter->SetText("FPS: " + to_string(m_FpsCounter));
		m_FpsCounter = 0;
		m_FpsTimer = 0.0f;
	}


	//update input
	auto command = dae::InputManager::GetInstance().HandleInput();

	if (command) command->Execute(m_pTestObject);

}

