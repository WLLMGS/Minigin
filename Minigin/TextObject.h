#pragma once
#include "SceneObject.h"
#include "Transform.h"
#include "GameObject.h"
#include <memory>

namespace dae
{
	class Font;
	class Texture2D;

	class TextObject : public GameObject
	{
	public:
		

		void SetText(const std::string& text);
		void SetPosition(float x, float y);


		explicit TextObject(const std::string& text, Font* font);
		virtual ~TextObject();
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;

	protected:
		virtual void Update(float elapsedSec) override;
		virtual void Render() const override;
	private:


		bool mNeedsUpdate;
		std::string mText;
		dae::Transform mTransform;
		Font* m_pFont;
		std::shared_ptr<Texture2D> mTexture;
	};

}
