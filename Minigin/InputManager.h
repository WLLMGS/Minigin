#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "GameActor.h"
#include <map>

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute(GameActor* actor) = 0;
};

class MoveRightCommand : public Command
{
public:
	virtual void Execute(GameActor* actor) override
	{
		actor->SetDirection(Right);
		actor->Transform()->SetRotation(0.0f);
	}
};

class MoveLeftCommand : public Command
{
public:
	virtual void Execute(GameActor* actor) override
	{
		actor->SetDirection(Left);
		actor->Transform()->SetRotation(180.0f);
	}
};

class MoveUpCommand :public Command
{
public:
	virtual void Execute(GameActor* actor) override
	{
		actor->SetDirection(Up);
		actor->Transform()->SetRotation(270.0f);
	}
};

class MoveDownCommand :public Command
{
public:
	virtual void Execute(GameActor* actor) override
	{
		actor->SetDirection(Down);
		actor->Transform()->SetRotation(90.0f);
	}
};


namespace dae
{

	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		DpadUp,
		DpadDown,
		DpadRight,
		DpadLeft
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		bool IsKeyPressed(int key);
		Command* HandleInput();
		void Clear();
		void GetThumbstickLeft(float& x, float& y);
		void GetThumbstickRight(float& x, float& y);

	private:
		XINPUT_STATE currentState{};
		Command* m_pRight = new MoveRightCommand();
		Command* m_pLeft = new MoveLeftCommand();
		Command* m_pUp = new MoveUpCommand();
		Command* m_pDown = new MoveDownCommand();
		map<int, bool> m_KeyMap;

	};



}
