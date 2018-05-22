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
		COIN = 2,
		GHOST = 3,
		MSPACMAN = 4,
		PILL = 5
	};
	enum FontName
	{
		DEFAULT = 0,
		MEDIUM = 1,
		BIG = 2
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
