#pragma once
#include<list>
#include<array>
#include<vector>
#include<typeinfo>
#include"gameObject.h"
#include"modelRenderer.h"

//�V�[���Ǘ�

class Scene
{
protected:
	//STL�̃��X�g�\��
	std::array<std::list<GameObject*>, 4> m_GameObject;

public:

	//�֐�
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
			//���X�g�N���A
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
			//�����_��
			//�폜���Ă������͍̂폜����
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
				if (typeid(*object) == typeid(T))//�^�𒲂ׂ�(RTTI���I�^���)
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
		std::vector<T*> objects;//STl�z��

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

