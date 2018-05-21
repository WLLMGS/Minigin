#pragma once
#include "Singleton.h"
#include <SDL.h>

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;

	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(SDL_Texture* texture, float x, float y) const;
		void RenderTexture(SDL_Texture* texture, float x, float y, float width, float height) const;
		void RenderTexture(SDL_Texture* texture, float x, float y, float width, float height, float angle, bool flip = false) const;
		void RenderTexture(SDL_Texture* texture, float x, float y, float width, float height, float angle
		,float sourceX, float sourceY, float sourceWidth, float sourceHeight, bool flip = false) const;

		void RenderFillRectangle(float x, float y, float width, float height);

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
	};
}

