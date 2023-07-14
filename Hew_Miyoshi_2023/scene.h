#pragma once
#include<list>
#include<array>
#include<vector>
#include<typeinfo>
#include"gameObject.h"
#include"modelRenderer.h"

//シーン管理

class Scene
{
protected:
	//STLのリスト構造
	std::array<std::list<GameObject*>, 4> m_GameObject;

public:

	//関数
	Scene() {}
	virtual ~Scene() {}

	virtual void Init() {}
	virtual void Uninit() {}
	virtual void Update() {}
	virtual void Draw() {}

	void InitBase()
	{
		Init();
	}

	void UninitBase()
	{
		for (auto& objectList : m_GameObject)
		{
			for (GameObject* object : objectList)
			{
				object->UninitBase(); 
				delete object;
			}
			//リストクリア
			objectList.clear();
		}

		Uninit();

		ModelRenderer::UnloadAll();
	}

	void UpdateBase()
	{
		for (auto& objectList : m_GameObject)
		{
			for (GameObject* object : objectList)
			{
				object->UpdateBase();
			}
			//ラムダ式
			//削除していいものは削除する
			objectList.remove_if([](GameObject* object) {return object->Destroy(); });
		}

		Update();
	}

	void DrawBase()
	{
		DirectX::SimpleMath::Matrix matrix;
		matrix = DirectX::SimpleMath::Matrix::Identity;

		for (auto& objectList : m_GameObject)
		{
			for (GameObject* object : objectList)
			{
				object->DrawBase(matrix);
			}		
		}

		Draw();
	}

	template<typename T>
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}

	template<typename T>
	T* GetGameObject()
	{
		for (auto& objectList : m_GameObject)
		{
			for (GameObject* object : objectList)
			{
				if (typeid(*object) == typeid(T))//型を調べる(RTTI動的型情報)
				{
					return (T*)object;
				}
			}			
		}

		return nullptr;
	}

	template<typename T>
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*> objects;//STl配列

		for (auto& objectList : m_GameObject)
		{
			for (GameObject* object : objectList)
			{
				if (typeid(*object) == typeid(T))
				{
					objects.push_back((T*)object);
				}
			}			
		}

		return objects;
	}
};

