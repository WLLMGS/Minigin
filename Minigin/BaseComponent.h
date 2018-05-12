#pragma once
namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent();
		GameObject* gameObject;

	protected:
		virtual void Update(float elapsedSec) = 0;
		virtual void Render() = 0;
		void SetGameObject(GameObject* pGameObject) { gameObject = pGameObject; }
		GameObject* GetGameObject() { return gameObject; }


		
		//add transform later


	private:
		friend class GameObject;

	};
}



