/**
 * @file Transition.h
 *
 * @brief ���̃t�@�C���� Transition �N���X�̒�`���܂�ł��܂��B
 */

#pragma once

#include "gameObject.h"

 /**
  * @class Transition
  *
  * @brief Transition �N���X�́A�t�F�[�h�C���ƃt�F�[�h�A�E�g�̃G�t�F�N�g�����Q�[���J�ڂ�\���܂��B
  */
class Transition : public GameObject
{
public:

    /**
     * @brief �J�ڂ̉\�ȏ�Ԃ�\���񋓌^�ł��B
     */
    enum class State
    {
        Stop,   ///< �t�F�[�h�C���I��
        In,     ///< �t�F�[�h�C��
        Out,    ///< �t�F�[�h�A�E�g
        Finish  ///< �t�F�[�h�A�E�g�I��
    };

private:
    float m_Alpha = 0.0f; ///< �t�F�[�h���ʂ𐧌䂷��A���t�@�l�ł��B
    State m_State = State::Stop; ///< �J�ڂ̌��݂̏�Ԃł��B
    class Sprite* m_Sprite{}; ///< �J�ڂɊ֘A�t����ꂽ�X�v���C�g�ւ̃|�C���^�ł��B

public:

    /**
     * @brief �J�ڃI�u�W�F�N�g�����������܂��B
     */
    void Init() override;

    /**
     * @brief �J�ڃI�u�W�F�N�g���X�V���܂��B
     */
    void Update() override;

    /**
     * @brief �J�ڂ̌��݂̏�Ԃ��擾���܂��B
     *
     * @return �J�ڂ̌��݂̏�ԁB
     */
    State GetState() { return m_State; }

    /**
     * @brief �t�F�[�h�C�������������܂��B
     */
    void FadeIn()
    {
        m_Alpha = 1.0f;
        m_State = State::In;
    }

    /**
     * @brief �t�F�[�h�A�E�g�����������܂��B
     */
    void FadeOut()
    {
        m_Alpha = 0.0f;
        m_State = State::Out;
    }
};
