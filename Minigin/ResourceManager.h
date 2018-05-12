#pragma once
#include "Singleton.h"
#include <vector>
#include <map>
#include <SDL.h>

using namespace std;

namespace dae
{
	enum TextureName
	{
		PACMAN = 0,
		WALL_1 = 1,
		CHARACTER_1_RUN = 2,
		CHARACTER_1_IDLE = 3,
		CHARACTER_1_ATTACK = 4,
		FIREBALL = 5,
		FIREBALL_DESTROY = 6,
		SPACESHIP_1 = 7,
		BULLET_BLUE = 8,
		SPACESHIPT_ENEMY_1 = 9,
		LARGE_EXPLOSION = 10,
		THRUSTER = 11,
		BULLET_ORANGE = 12,
		COIN = 13,
		GHOST = 14
	};
	enum FontName
	{
		DEFAULT = 0
	};

	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
		std::string mDataPath;
	public:
		ResourceManager() = default;

		void Clear();
		void Init(std::string&& data);

		SDL_Texture* RequestTexture(const TextureName name);
		Font* RequestFont(const FontName name);
	private:
		void InitResources();
		void InitTexture(const std::string& file, const TextureName name);
		void InitFont(const std::string& file,int size, const FontName name);
		map<int, SDL_Texture*> m_pTextures;
		map<int, Font*> m_pFonts;
	};

}
