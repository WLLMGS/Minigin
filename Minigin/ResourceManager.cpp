#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"


void dae::ResourceManager::Clear()
{
	//clear all textures
	for(pair<int, Texture2D*> p : m_pTextures)
	{
		delete p.second;
		p.second = nullptr;
	}

}

//OK
void dae::ResourceManager::Init(std::string&& dataPath)
{
	mDataPath = std::move(dataPath);

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::stringstream ss; ss << "Failed to load support for png: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) {
		std::stringstream ss; ss << "Failed to load support for png: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	if (TTF_Init() != 0) {
		std::stringstream ss; ss << "Failed to load support for fonts: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	InitResources();
}

dae::Texture2D* dae::ResourceManager::RequestTexture(const TextureName name)
{
	return (m_pTextures[name] != nullptr) ? m_pTextures[name] : nullptr;
}

dae::Font* dae::ResourceManager::RequestFont(const FontName name)
{
	return (m_pFonts[name] != nullptr) ? m_pFonts[name] : nullptr;
}

void dae::ResourceManager::InitResources()
{
	InitFont("SansSerifFont.ttf", 24, DEFAULT);
	InitTexture("pacman.png", PACMAN);
}

void dae::ResourceManager::InitTexture(const std::string& file, const TextureName name)
{
	std::string fullPath = (mDataPath + "Sprites/" + file).c_str();
	SDL_Texture *texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) {
		std::stringstream ss; ss << "Failed to load texture: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	Texture2D* texture2D = new Texture2D(texture);

	m_pTextures[name] = texture2D;
}

void dae::ResourceManager::InitFont(const std::string& file,int size, const FontName name)
{
	std::string fullPath = (mDataPath + "Fonts/" + file).c_str();
	
	m_pFonts[name] = new Font(fullPath, size);
}
