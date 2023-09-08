#pragma once
#include "scene.h"
#include "StageEditor.h"

/**
 * @brief �Q�[���V�[�� Game �N���X
 */
class Game : public Scene
{
private:
    class Transition* m_Transition{}; /**< ��ʑJ�ڂ��Ǘ�����I�u�W�F�N�g */
    class FadeUI* m_Fade{}; /**< �t�F�[�hUI���Ǘ�����I�u�W�F�N�g */

    bool m_Goal = false; /**< �S�[�����Ă��邩�ǂ����������t���O */

public:
    /**
     * @brief �Q�[���V�[���̏������֐�
     */
    void Init() override;

    /**
     * @brief �Q�[���V�[���̍X�V�֐�
     */
    void Update() override;

    /**
     * @brief StageEditor �V�[���ō쐬�����X�e�[�W���t�@�C�����烍�[�h����֐�
     * @param filename �t�@�C����
     */
    void LoadpositionToFile(const std::string& filename);
};
