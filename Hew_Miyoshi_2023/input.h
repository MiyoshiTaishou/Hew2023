#pragma once
#include <GamePad.h>

/**
 * @brief �R���g���[���[�̃X�e�B�b�N������\���񋓌^
 */
enum BUTTON
{
    LUP,     ///< ���X�e�B�b�N��
    LDOWN,   ///< ���X�e�B�b�N��
    LLEFT,   ///< ���X�e�B�b�N��
    LRIGHT,  ///< ���X�e�B�b�N�E
    RUP,     ///< �E�X�e�B�b�N��
    RDOWN,   ///< �E�X�e�B�b�N��
    RLEFT,   ///< �E�X�e�B�b�N��
    RRIGHT   ///< �E�X�e�B�b�N�E
};

/**
 * @brief �R���g���[���[�̃{�^���̏�Ԃ�\���񋓌^
 */
enum STATE
{
    UP = 0,         ///< �{�^����������Ă�����
    HELD = 1,       ///< �{�^����������Ă�����
    RELEASED = 2,   ///< �{�^���������ꂽ���
    PRESSED = 3     ///< �{�^���������ꂽ���
};

/**
 * @brief ���͏������Ǘ�����N���X
 */
class Input
{
private:
    static BYTE m_OldKeyState[256];
    static BYTE m_KeyState[256];

    // �p�b�h�̔���
    static DirectX::GamePad m_GamePad;
    static DirectX::GamePad::State m_State;
    static DirectX::GamePad::ButtonStateTracker m_StateTracker;

public:
   
    static void Init();
    static void Update();

    /**
     * @brief �L�[�{�[�h�̃L�[��������Ă��邩���擾����
     * @param[in] KeyCode �L�[�R�[�h
     * @return �L�[��������Ă���ꍇ��true�A����ȊO��false
     */
    static bool GetKeyPress(BYTE KeyCode);

    /**
     * @brief �L�[�{�[�h�̃L�[�������ꂽ�u�Ԃ����擾����
     * @param[in] KeyCode �L�[�R�[�h
     * @return �L�[�������ꂽ�u�Ԃ̏ꍇ��true�A����ȊO��false
     */
    static bool GetKeyTrigger(BYTE KeyCode);

    /**
     * @brief �Q�[���p�b�h�̃{�^���̏�Ԃ��擾����
     * @param[in] button �{�^���̗񋓌^
     * @param[in] _buttonState �{�^���̏�ԁiUP/HELD/RELEASED/PRESSED�j
     * @return �{�^���̏�Ԃ��w�肳�ꂽ���̂ƈ�v����ꍇ��true�A����ȊO��false
     */
    static bool GetGamePad(BUTTON button, STATE _buttonState);
};
