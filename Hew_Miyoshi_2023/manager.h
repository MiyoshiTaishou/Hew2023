#pragma once
#include <cinttypes>
#include "scene.h"

// �O���Q��
class Application;

class Manager
{
private:
    static class Scene* m_Scene; // ���݂̃V�[���ւ̃|�C���^

public:
    /**
     * @brief Manager�N���X�̏�����
     * @param ap �A�v���P�[�V�����ւ̃|�C���^
     */
    static void Init(Application* ap);

    /**
     * @brief Manager�N���X�̏I������
     */
    static void Uninit();

    /**
     * @brief Manager�N���X�̍X�V
     * @param d �o�ߎ���
     */
    static void Update(uint64_t d);

    /**
     * @brief Manager�N���X�̕`��
     * @param d �o�ߎ���
     */
    static void Draw(uint64_t d);

    /**
     * @brief ���݂̃V�[�����擾���܂��B
     * @return ���݂̃V�[���ւ̃|�C���^
     */
    static class Scene* GetScene()
    {
        return m_Scene;
    }

    /**
     * @brief �V�����V�[����ݒ肵�܂��B
     * @tparam T �ݒ肷��V�����V�[���̃N���X�^
     */
    template <typename T>
    static void SetScene()
    {
        // ���݂̃V�[�����N���A���ĐV�����V�[����ݒ�
        if (m_Scene)
        {
            m_Scene->UninitBase();
            delete m_Scene;
        }

        m_Scene = new T();
        m_Scene->InitBase();
    }
};
