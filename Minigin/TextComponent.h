#pragma once
#include "BaseComponent.h"
#include "ResourceManager.h"
#include "Font.h"
#include "Texture2D.h"

class TextComponent : public dae::BaseComponent
{
public:
	TextComponent(dae::FontName fontName, const SDL_Color& color, const string& text = "hello world");
	~TextComponent();
	virtual void Update(float elapsedSec) override;
	virtual void Render() override;
	void SetColor(const SDL_Color& color);
	void SetText(const string& text);
private:
	dae::Font* m_pFont = nullptr;
	SDL_Color m_Color{255,255,255};
	SDL_Texture* m_pTexture = nullptr;
};

