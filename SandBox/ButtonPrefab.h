#pragma once
#include "GameObject.h"
#include <functional>
#include <SDL.h>
#include "ResourceManager.h"

class ButtonPrefab : public dae::GameObject
{
public:
	ButtonPrefab(dae::FontName font, SDL_Color color, string text);
	~ButtonPrefab();

	void SetSelected(bool selected);
	bool IsSelected() const;

	void SetAction(function<void()> action);
	void Activate();
private:
	bool m_IsSelected = false;

	function<void()> m_Action;
	SDL_Color m_Color;
};

