#pragma once

#include "renderer.h"
#include <list>
#include <SimpleMath.h>
#include "component.h"

/**
 * @brief �Q�[���I�u�W�F�N�g�̊�{�N���X�ł��B
 */
class GameObject
{
protected:
    bool m_Destroy = false; ///< �I�u�W�F�N�g�̔j���t���O
    DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f); ///< �I�u�W�F�N�g�̈ʒu
    DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f); ///< �I�u�W�F�N�g�̉�]
    DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f); ///< �I�u�W�F�N�g�̃X�P�[��

    std::list<Component*> m_Component; ///< �I�u�W�F�N�g�ɃA�^�b�`���ꂽ�R���|�[�l���g�̃��X�g
    std::list<GameObject*> m_ChildGameObject; ///< �q�I�u�W�F�N�g�̃��X�g

public:
    /**
     * @brief GameObject�N���X�̃R���X�g���N�^
     */
    GameObject() {}

    /**
     * @brief GameObject�N���X�̃f�X�g���N�^
     */
    virtual ~GameObject() {}

    /**
     * @brief �I�u�W�F�N�g�̈ʒu���擾���܂��B
     * @return �I�u�W�F�N�g�̈ʒu
     */
    DirectX::SimpleMath::Vector3 GetPosition() { return m_Position; }

    /**
     * @brief �I�u�W�F�N�g�̉�]���擾���܂��B
     * @return �I�u�W�F�N�g�̉�]
     */
    DirectX::SimpleMath::Vector3 GetRotation() { return m_Rotation; }

    /**
     * @brief �I�u�W�F�N�g�̃X�P�[�����擾���܂��B
     * @return �I�u�W�F�N�g�̃X�P�[��
     */
    DirectX::SimpleMath::Vector3 GetScale() { return m_Scale; }

    /**
     * @brief �I�u�W�F�N�g�̈ʒu��ݒ肵�܂��B
     * @param Position �V�����ʒu
     */
    void SetPosition(DirectX::SimpleMath::Vector3 Position) { m_Position = Position; }

    /**
     * @brief �I�u�W�F�N�g�̉�]��ݒ肵�܂��B
     * @param Rotation �V������]
     */
    void SetRotation(DirectX::SimpleMath::Vector3 Rotation) { m_Rotation = Rotation; }

    /**
     * @brief �I�u�W�F�N�g�̃X�P�[����ݒ肵�܂��B
     * @param Scale �V�����X�P�[��
     */
    void SetScale(DirectX::SimpleMath::Vector3 Scale) { m_Scale = Scale; }

    /**
     * @brief �I�u�W�F�N�g�̑O���x�N�g�����擾���܂��B
     * @return �I�u�W�F�N�g�̑O���x�N�g��
     */
    DirectX::SimpleMath::Vector3 GetForward()
    {
        // �O���x�N�g�����v�Z���鏈��
        DirectX::SimpleMath::Matrix rot;
        rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);

        DirectX::SimpleMath::Vector3 forward;
        forward.x = rot._31;
        forward.y = rot._32;
        forward.z = rot._33;

        return forward;
    }

    /**
     * @brief �I�u�W�F�N�g�̉������x�N�g�����擾���܂��B
     * @return �I�u�W�F�N�g�̉������x�N�g��
     */
    DirectX::SimpleMath::Vector3 GetSide()
    {
        // �������x�N�g�����v�Z���鏈��
        DirectX::SimpleMath::Matrix rot;
        rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(m_Rotation.y - 89.535f, m_Rotation.x, m_Rotation.z);

        DirectX::SimpleMath::Vector3 side;
        side.x = rot._31;
        side.y = rot._32;
        side.z = rot._33;

        return side;
    }

    /**
     * @brief �I�u�W�F�N�g�̔j���t���O��ݒ肵�܂��B
     */
    void SetDestroy() { m_Destroy = true; }

    /**
     * @brief �I�u�W�F�N�g��j�����܂��B
     * @return �I�u�W�F�N�g���j�����ꂽ�ꍇ��true�A����ȊO��false
     */
    bool Destroy()
    {
        if (m_Destroy)
        {
            UninitBase();
            delete this;
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief �I�u�W�F�N�g�̏��������s���܂��B
     */
    virtual void Init() {}

    /**
     * @brief �I�u�W�F�N�g�̏I���������s���܂��B
     */
    virtual void Uninit() {}

    /**
     * @brief �I�u�W�F�N�g�̍X�V�������s���܂��B
     */
    virtual void Update() {}

    /**
     * @brief �I�u�W�F�N�g�̕`�揈�����s���܂��B
     */
    virtual void Draw() {}

    /**
     * @brief �I�u�W�F�N�g�ɐV�����R���|�[�l���g��ǉ����܂��B
     * @tparam T �ǉ�����R���|�[�l���g�̌^
     * @return �ǉ����ꂽ�R���|�[�l���g�ւ̃|�C���^
     */
    template <typename T>
    T* AddComponent()
    {
        T* component = new T(this);
        m_Component.push_back(component);
        ((Component*)component)->Init();

        return component;
    }

    /**
     * @brief �I�u�W�F�N�g����w�肳�ꂽ�^�̃R���|�[�l���g���擾���܂��B
     * @tparam T �擾����R���|�[�l���g�̌^
     * @return �R���|�[�l���g�ւ̃|�C���^
     */
    template <typename T>
    T* GetComponent()
    {
        for (Component* component : m_Component)
        {
            if (typeid(*component) == typeid(T))
            {
                return (T*)component;
            }
        }
        return nullptr;
    }

    /**
     * @brief �q�I�u�W�F�N�g��ǉ����܂��B
     * @tparam T �ǉ�����q�I�u�W�F�N�g�̌^
     * @return �ǉ����ꂽ�q�I�u�W�F�N�g�ւ̃|�C���^
     */
    template <typename T>
    T* AddChild()
    {
        T* child = new T();
        m_ChildGameObject.push_back(child);
        child->InitBase();

        return child;
    }

    /**
     * @brief �I�u�W�F�N�g�Ƃ��̎q�I�u�W�F�N�g�A�R���|�[�l���g�����������܂��B
     */
    void InitBase()
    {
        Init();
    }

    /**
     * @brief �I�u�W�F�N�g�Ƃ��̎q�I�u�W�F�N�g�A�R���|�[�l���g���I���������܂��B
     */
    void UninitBase()
    {
        Uninit();

        for (GameObject* child : m_ChildGameObject)
        {
            child->UninitBase();
            delete child;
        }

        for (Component* component : m_Component)
        {
            component->Uninit();
            delete component;
        }
        m_Component.clear(); // ���X�g�̃N���A
        m_ChildGameObject.clear();
    }

    /**
     * @brief �I�u�W�F�N�g�Ƃ��̎q�I�u�W�F�N�g�A�R���|�[�l���g���X�V���܂��B
     */
    void UpdateBase()
    {
        for (GameObject* child : m_ChildGameObject)
        {
            child->UpdateBase();
        }

        for (Component* component : m_Component)
        {
            component->Update();
        }

        Update();
    }

    /**
     * @brief �I�u�W�F�N�g�Ƃ��̎q�I�u�W�F�N�g�A�R���|�[�l���g��`�悵�܂��B
     * @param ParentMatrix �e�I�u�W�F�N�g�̃��[���h�s��
     */
    void DrawBase(DirectX::SimpleMath::Matrix ParentMatrix)
    {
        // �}�g���N�X�ݒ�
        DirectX::SimpleMath::Matrix world, scale, rot, trans;
        scale = DirectX::SimpleMath::Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);
        rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
        trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
        world = scale * rot * trans * ParentMatrix;

        for (GameObject* child : m_ChildGameObject)
        {
            child->DrawBase(world);
        }

        Renderer::SetWorldMatrix(&world);

        for (Component* component : m_Component)
        {
            component->Draw();
        }

        Draw();
    }
};