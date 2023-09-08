#pragma once
#include <list>
#include <array>
#include <vector>
#include <typeinfo>
#include "gameObject.h"
#include "modelRenderer.h"

/**
 * @brief �V�[���Ǘ��N���X Scene
 */
class Scene
{
protected:
    std::array<std::list<GameObject*>, 4> m_GameObject; /**< �Q�[���I�u�W�F�N�g�̃��X�g�\�� */

public:
    /**
     * @brief �R���X�g���N�^
     */
    Scene() {}

    /**
     * @brief �f�X�g���N�^
     */
    virtual ~Scene() {}

    /**
     * @brief �V�[���̏������֐�
     */
    virtual void Init() {}

    /**
     * @brief �V�[���̏I���֐�
     */
    virtual void Uninit() {}

    /**
     * @brief �V�[���̍X�V�֐�
     */
    virtual void Update() {}

    /**
     * @brief �V�[���̕`��֐�
     */
    virtual void Draw() {}

    /**
     * @brief ��{�̏������֐�
     */
    void InitBase()
    {
        Init();
    }

    /**
     * @brief ��{�̏I���֐�
     */
    void UninitBase()
    {
        for (auto& objectList : m_GameObject)
        {
            for (GameObject* object : objectList)
            {
                object->UninitBase();
                delete object;
            }
            objectList.clear();
        }

        Uninit();

        ModelRenderer::UnloadAll();
    }

    /**
     * @brief ��{�̍X�V�֐�
     */
    void UpdateBase()
    {
        for (auto& objectList : m_GameObject)
        {
            for (GameObject* object : objectList)
            {
                object->UpdateBase();
            }
            objectList.remove_if([](GameObject* object) { return object->Destroy(); });
        }

        Update();
    }

    /**
     * @brief ��{�̕`��֐�
     */
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

    /**
     * @brief �Q�[���I�u�W�F�N�g��ǉ�����e���v���[�g�֐�
     * @tparam T �ǉ�����Q�[���I�u�W�F�N�g�̌^
     * @param Layer �Q�[���I�u�W�F�N�g�̃��C��
     * @return �ǉ����ꂽ�Q�[���I�u�W�F�N�g�̃|�C���^
     */
    template<typename T>
    T* AddGameObject(int Layer)
    {
        T* gameObject = new T();
        m_GameObject[Layer].push_back(gameObject);
        gameObject->Init();

        return gameObject;
    }

    /**
     * @brief ����̌^�̃Q�[���I�u�W�F�N�g���擾����e���v���[�g�֐�
     * @tparam T �擾�������Q�[���I�u�W�F�N�g�̌^
     * @return ����̌^�̃Q�[���I�u�W�F�N�g�̃|�C���^
     */
    template<typename T>
    T* GetGameObject()
    {
        for (auto& objectList : m_GameObject)
        {
            for (GameObject* object : objectList)
            {
                if (typeid(*object) == typeid(T))
                {
                    return (T*)object;
                }
            }
        }

        return nullptr;
    }

    /**
     * @brief ����̌^�̃Q�[���I�u�W�F�N�g���擾����e���v���[�g�֐�
     * @tparam T �擾�������Q�[���I�u�W�F�N�g�̌^
     * @return ����̌^�̃Q�[���I�u�W�F�N�g�̃|�C���^�̃x�N�^�[
     */
    template<typename T>
    std::vector<T*> GetGameObjects()
    {
        std::vector<T*> objects;

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
