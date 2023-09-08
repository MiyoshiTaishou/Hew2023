#pragma once
#include <cinttypes>
#include "scene.h"

// �O���Q��
class Application;

/**
 * @brief �V�[���ɂ���I�u�W�F�N�g���Ǘ����A�`�悷��N���X
 */
class Manager
{
private:

    // ���݂̃V�[��
    static class Scene* m_Scene;

public:

    /**
     * @brief Manager�N���X�̏�����
     * @param[in] ap Application�N���X�ւ̃|�C���^
     */
    static void Init(Application* ap);

    /**
     * @brief Manager�N���X�̏I������
     */
    static void Uninit();

    /**
     * @brief Manager�N���X�̍X�V����
     * @param[in] d �X�V�ɂ����鎞�ԁi�~���b�j
     */
    static void Update(uint64_t d);

    /**
     * @brief Manager�N���X�̕`�揈��
     * @param[in] d �`��ɂ����鎞�ԁi�~���b�j
     */
    static void Draw(uint64_t d);

    /**
     * @brief ���݂̃V�[�����擾����
     * @return ���݂̃V�[���ւ̃|�C���^
     */
    static class Scene* GetScene()
    {
        return m_Scene;
    }

    /**
     * @brief �V�����V�[����ݒ肷��
     * @tparam T �V�����V�[���̌^
     */
    template <typename T>
    static void SetScene()
    {
        if (m_Scene)
        {
            m_Scene->UninitBase();
            delete m_Scene;
        }

        m_Scene = new T();
        m_Scene->InitBase();
    }
};
