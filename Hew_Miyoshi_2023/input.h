#pragma once
#include    <windows.h>
#include    <GamePad.h>

/**
 * @brief �{�^���̗񋓌^
 */
enum BUTTON
{
    LUP,    /**< ����{�^�� */
    LDOWN,  /**< �����{�^�� */
    LLEFT,  /**< �����{�^�� */
    LRIGHT, /**< ���E�{�^�� */
    RUP,    /**< �E��{�^�� */
    RDOWN,  /**< �E���{�^�� */
    RLEFT,  /**< �E���{�^�� */
    RRIGHT, /**< �E�E�{�^�� */
};

/**
 * @brief �{�^���̏�Ԃ�\���񋓌^
 */
enum STATE
{
    UP = 0,         /**< �{�^����������Ă��� */
    HELD = 1,       /**< �{�^���������������Ă��� */
    RELEASED = 2,   /**< �{�^���������[�X���ꂽ */
    PRESSED = 3,    /**< �{�^���������ꂽ */
};

/**
 * @brief ���͊Ǘ��N���X
 */
class Input
{
private:
    static BYTE m_OldKeyState[256];                 /**< �O��̃L�[�{�[�h�̏�� */
    static BYTE m_KeyState[256];                    /**< ���݂̃L�[�{�[�h�̏�� */

    // �Q�[���p�b�h�̔���
    static DirectX::GamePad m_GamePad;              /**< �Q�[���p�b�h�̃I�u�W�F�N�g */
    static DirectX::GamePad::State m_State;        /**< �Q�[���p�b�h�̏�� */
    static DirectX::GamePad::ButtonStateTracker m_StateTracker; /**< �Q�[���p�b�h�̃{�^���̏�Ԃ�ǐՂ���g���b�J�[ */

public:
    /**
     * @brief ���͊Ǘ��N���X�̏�����
     */
    static void Init();

    /**
     * @brief ���͊Ǘ��N���X�̏I������
     */
    static void Uninit();

    /**
     * @brief ���͏��̍X�V
     */
    static void Update();

    /**
     * @brief �w�肵���L�[�R�[�h�̃L�[��������Ă��邩���擾���܂��B
     * @param KeyCode �L�[�R�[�h
     * @return �L�[��������Ă���ꍇ��true�A����ȊO��false
     */
    static bool GetKeyPress(BYTE KeyCode);

    /**
     * @brief �w�肵���L�[�R�[�h�̃L�[���g���K�[���ꂽ�����擾���܂��B
     * @param KeyCode �L�[�R�[�h
     * @return �L�[���g���K�[���ꂽ�ꍇ��true�A����ȊO��false
     */
    static bool GetKeyTrigger(BYTE KeyCode);

    /**
     * @brief �w�肵���Q�[���p�b�h�̃{�^���̏�Ԃ��擾���܂��B
     * @param button �{�^��
     * @param _buttonState �{�^���̏��
     * @return �{�^���̏�Ԃ��w�肵����Ԃł���ꍇ��true�A����ȊO��false
     */
    static bool GetGamePad(BUTTON button, STATE _buttonState);

    static void Vibration(int player, float leftMotor, float rightMotor, float leftTrigger, float rightTrigger);
};
