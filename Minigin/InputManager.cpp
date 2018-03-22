#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include <XInput.h>


bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &currentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) 
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	case ControllerButton::DpadUp:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case ControllerButton::DpadDown:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case ControllerButton::DpadRight:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case ControllerButton::DpadLeft:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	default: return false;
	}

}

Command* dae::InputManager::HandleInput()
{
	if (IsPressed(ControllerButton::DpadRight)) return m_pRight;
	if (IsPressed(ControllerButton::DpadLeft)) return m_pLeft;
	if (IsPressed(ControllerButton::DpadUp)) return m_pUp;
	if (IsPressed(ControllerButton::DpadDown)) return m_pDown;
	return nullptr;
}

void dae::InputManager::Clear()
{
	delete m_pRight;
	m_pRight = nullptr;

	delete m_pLeft;
	m_pLeft = nullptr;

	delete m_pUp;
	m_pUp = nullptr;

	delete m_pDown;
	m_pDown = nullptr;
}



