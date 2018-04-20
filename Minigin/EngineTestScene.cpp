#include "MiniginPCH.h"
#include "EngineTestScene.h"
#include "ResourceManager.h"
#include "BaseComponent.h"

#include "SpriteComponent.h"
#include "InputManager.h"
#include "WallPrefab.h"
#include "PacmanPrefab.h"
#include "LevelLoader.h"


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
	/*auto sprite = new dae::SpriteComponent(dae::TextureName::PACMAN);
	sprite->SetAnimated(true);
	sprite->SetAnimationParameters(3, 9, 10.0f, 9.0f);
	m_pTestObject->AddComponent(sprite);
	m_pTestObject->Translate(10, 200, 1);
	m_pTestObject->Transform()->SetScale(1, 1, 1);
	m_pTestObject->Transform()->SetRotation(0.0f);*/

	AddChild(m_pTestObject);

	//Logger::GetInstance().Log("HELLO WORLD");

}

EngineTestScene::~EngineTestScene() = default;



void EngineTestScene::Update(float elapsedSec)
{
	m_FpsTimer += elapsedSec;
	++m_FpsCounter;

	if((m_FpsTimer) >= 1.0f)
	{	
		string message = "X: " + to_string(m_pTestObject->Transform()->GetPosition().x) + " Y: " + to_string(m_pTestObject->Transform()->GetPosition().y);
		Logger::GetInstance().Log(message);
		
		//Logger::GetInstance().Log(message);
		m_pFpsComp->SetText("FPS: " + to_string(m_FpsCounter));
		m_FpsCounter = 0;
		m_FpsTimer = 0.0f;

	}

	
	//update input
	auto command = dae::InputManager::GetInstance().HandleInput();

	if (command) command->Execute(m_pTestObject);

}

