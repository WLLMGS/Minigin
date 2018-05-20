#include "stdafx.h"
#include "ButtonPrefab.h"
#include "TextComponent.h"


ButtonPrefab::ButtonPrefab(dae::FontName font, SDL_Color color, string text) :
m_Color(color)
{
	auto txt = new TextComponent(font, color, text);
	AddComponent(txt);
}


ButtonPrefab::~ButtonPrefab()
{
}

void ButtonPrefab::SetSelected(bool selected)
{
	m_IsSelected = selected;
	auto txt = GetComponent<TextComponent>();

	if(m_IsSelected)
	{
		txt->SetColor({ 255,255,0,255 });
	}
	else
	{
		txt->SetColor(m_Color);
	}
}

bool ButtonPrefab::IsSelected() const
{
	return m_IsSelected;
}

void ButtonPrefab::SetAction(function<void()> action)
{
	m_Action = action;
}

void ButtonPrefab::Activate()
{
	m_Action();
}
