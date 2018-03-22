#pragma once
namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent();
		GameObject* GetGameObject() { return m_pGameObject; }
		

	protected:
		virtual void Update(float elapsedSec) = 0;
		virtual void Render() = 0;

		GameObject* m_pGameObject;
		//add transform later


	private:
		friend class GameObject;

	};
}



