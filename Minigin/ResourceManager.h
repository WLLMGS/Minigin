#pragma once
#include "Singleton.h"
#include <vector>
#include <map>

using namespace std;

namespace dae
{
	enum TextureName
	{
		PACMAN = 0
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

		Texture2D* RequestTexture(const TextureName name);
		Font* RequestFont(const FontName name);

		

	private:
		void InitResources();
		void InitTexture(const std::string& file, const TextureName name);
		void InitFont(const std::string& file,int size, const FontName name);
		map<int, Texture2D*> m_pTextures;
		map<int, Font*> m_pFonts;
	};

}
