#pragma once
#include "gameObject.h"

/**
 * @brief ��ʑJ�ڗp�̃N���X
 */
class Transition : public GameObject
{
public:
    /**
     * @brief ��ʑJ�ڂ̏�Ԃ�\���񋓌^
     */
    enum class State
    {
        Stop,   ///< �t�F�[�h�C���I��
        In,     ///< �t�F�[�h�C��
        Out,    ///< �t�F�[�h�A�E�g
        Finish  ///< �t�F�[�h�A�E�g�I��
    };

private:
    float m_Alpha = 0.0f;         ///< �����x�i�A���t�@�l�j
    State m_State = State::Stop; ///< ��ʑJ�ڂ̏��
    class Sprite* m_Sprite{};   ///< �X�v���C�g�N���X�ւ̃|�C���^

public:
    /**
     * @brief �������֐�
     */
    void Init() override;

    /**
     * @brief �X�V�֐�
     */
    void Update() override;

    /**
     * @brief ��ʑJ�ڂ̏�Ԃ��擾
     * @return ��ʑJ�ڂ̏�ԁiState�񋓌^�j
     */
    State GetState() { return m_State; }

    /**
     * @brief �t�F�[�h�C���̏�������
     */
    void FadeIn()
    {
        m_Alpha = 1.0f;
        m_State = State::In;
    }

    /**
     * @brief �t�F�[�h�A�E�g�̏�������
     */
    void FadeOut()
    {
        m_Alpha = 0.0f;
        m_State = State::Out;
    }
};
