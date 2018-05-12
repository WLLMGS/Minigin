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
			m_KeyMap[e.key.keysym.sym] = true;
		}
		if(e.type == SDL_KEYUP)
		{
			m_KeyMap[e.key.keysym.sym] = false;
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

bool dae::InputManager::IsKeyPressed(int key)
{
	return m_KeyMap[key];
	
}

Command* dae::InputManager::HandleInput()
{
	//controller
	if (IsPressed(ControllerButton::DpadRight)) return m_pRight;
	if (IsPressed(ControllerButton::DpadLeft)) return m_pLeft;
	if (IsPressed(ControllerButton::DpadUp)) return m_pUp;
	if (IsPressed(ControllerButton::DpadDown)) return m_pDown;

	//Keyboard
	//2 keys because of azerty / qwerty
	if (IsKeyPressed(SDLK_z) || IsKeyPressed(SDLK_w)) return m_pUp;
	if (IsKeyPressed(SDLK_s)) return m_pDown;
	//2 keys because of azerty / qwerty
	if (IsKeyPressed(SDLK_q) || IsKeyPressed(SDLK_a)) return m_pLeft;
	if (IsKeyPressed(SDLK_d)) return m_pRight;

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

void dae::InputManager::GetThumbstickLeft(float& x, float& y)
{
	x = currentState.Gamepad.sThumbLX;
	y = -float(currentState.Gamepad.sThumbLY);

	x /= 32768.0;
	y /= 32768.0;

	if (abs(x) < 0.19f) x = 0.0f;
	if (abs(y) < 0.19f) y = 0.0f;

}

void dae::InputManager::GetThumbstickRight(float& x, float& y)
{
	x = currentState.Gamepad.sThumbRX;
	y = -float(currentState.Gamepad.sThumbRY);

	x /= 32768.0;
	y /= 32768.0;

	if (abs(x) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) x = 0.0f;
	if (abs(y) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) y = 0.0f;

}



