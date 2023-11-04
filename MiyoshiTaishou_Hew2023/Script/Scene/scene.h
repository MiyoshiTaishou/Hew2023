#pragma once
#include <list>
#include <array>
#include <vector>
#include <typeinfo>
#include "../Object/gameObject.h"
#include "../Render/modelRenderer.h"

/**
 * @brief �V�[���Ǘ��N���X
 */
class Scene
{
protected:
    // STL�̃��X�g�\��
    std::array<std::list<GameObject*>, 4> m_GameObject;

public:
    /**
     * @brief Scene�N���X�̃R���X�g���N�^
     */
    Scene() {}

    /**
     * @brief Scene�N���X�̃f�X�g���N�^
     */
    virtual ~Scene() {}

    /**
     * @brief �V�[���̏��������s���܂��B
     */
    virtual void Init() {}

    /**
     * @brief �V�[���̏I���������s���܂��B
     */
    virtual void Uninit() {}

    /**
     * @brief �V�[���̍X�V�������s���܂��B
     */
    virtual void Update() {}

    /**
     * @brief �V�[���̕`�揈�����s���܂��B
     */
    virtual void Draw() {}

    /**
     * @brief �V�[���̊�{�������������s���܂��B
     */
    void InitBase()
    {
        Init();
    }

    /**
     * @brief �V�[���̊�{�I���������s���܂��B
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
            // ���X�g�N���A
            objectList.clear();
        }

        Uninit();

        ModelRenderer::UnloadAll();
    }

    /**
     * @brief �V�[���̊�{�X�V�������s���܂��B
     */
    void UpdateBase()
    {
        for (auto& objectList : m_GameObject)
        {
            for (GameObject* object : objectList)
            {
                object->UpdateBase();
            }
            // �����_��
            // �폜���Ă������͍̂폜����
            objectList.remove_if([](GameObject* object) { return object->Destroy(); });
        }

        Update();
    }

    /**
     * @brief �V�[���̊�{�`�揈�����s���܂��B
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
     * @brief �w�肵�����C���[�ɐV����GameObject��ǉ����܂��B
     * @tparam T �ǉ�����GameObject�̌^
     * @param Layer ���C���[�ԍ�
     * @return �ǉ����ꂽGameObject�ւ̃|�C���^
     */
    template <typename T>
    T* AddGameObject(int Layer)
    {
        T* gameObject = new T();
        m_GameObject[Layer].push_back(gameObject);
        gameObject->Init();

        return gameObject;
    }

    /**
     * @brief �w�肵���^��GameObject���擾���܂��B
     * @tparam T �擾����GameObject�̌^
     * @return GameObject�ւ̃|�C���^
     */
    template <typename T>
    T* GetGameObject()
    {
        for (auto& objectList : m_GameObject)
        {
            for (GameObject* object : objectList)
            {
                if (typeid(*object) == typeid(T)) // �^�𒲂ׂ� (RTTI���I�^���)
                {
                    return (T*)object;
                }
            }
        }

        return nullptr;
    }

    /**
     * @brief �w�肵���^�̂��ׂĂ�GameObject���擾���܂��B
     * @tparam T �擾����GameObject�̌^
     * @return GameObject�̃x�N�^�[
     */
    template <typename T>
    std::vector<T*> GetGameObjects()
    {
        std::vector<T*> objects; // STL�z��

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
