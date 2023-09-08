#include "main.h"
#include <cstring> // for memset
#include "input.h"

using namespace DirectX;

/**
 * @brief �L�[�{�[�h�̓��͏����Ǘ�����N���X
 */
BYTE Input::m_OldKeyState[256];
BYTE Input::m_KeyState[256];
DirectX::GamePad Input::m_GamePad;
DirectX::GamePad::ButtonStateTracker Input::m_StateTracker;
DirectX::GamePad::State Input::m_State;

/**
 * @brief Input�N���X�̏�����
 */
void Input::Init()
{
    memset(m_OldKeyState, 0, 256);
    memset(m_KeyState, 0, 256);
}

/**
 * @brief �L�[�{�[�h�ƃQ�[���p�b�h�̓��͏��̍X�V
 */
void Input::Update()
{
    memcpy(m_OldKeyState, m_KeyState, 256);
    GetKeyboardState(m_KeyState);

    m_State = m_GamePad.GetState(0);
    m_StateTracker.Update(m_State);
}

/**
 * @brief �w�肳�ꂽ�L�[�R�[�h�̃L�[��������Ă��邩���擾����
 * @param[in] KeyCode �L�[�R�[�h
 * @return �L�[��������Ă���ꍇ��true�A����ȊO��false
 */
bool Input::GetKeyPress(BYTE KeyCode)
{
    return (m_KeyState[KeyCode] & 0x80);
}

/**
 * @brief �w�肳�ꂽ�L�[�R�[�h�̃L�[�������ꂽ�u�Ԃ����擾����
 * @param[in] KeyCode �L�[�R�[�h
 * @return �L�[�������ꂽ�u�Ԃ̏ꍇ��true�A����ȊO��false
 */
bool Input::GetKeyTrigger(BYTE KeyCode)
{
    return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

/**
 * @brief �Q�[���p�b�h�̃{�^���̏�Ԃ��擾����
 * @param[in] button �{�^���̗񋓌^
 * @param[in] _buttonState �{�^���̏�ԁiUP/HELD/RELEASED/PRESSED�j
 * @return �{�^���̏�Ԃ��w�肳�ꂽ���̂ƈ�v����ꍇ��true�A����ȊO��false
 */
bool Input::GetGamePad(BUTTON button, STATE _buttonState)
{
    switch (button)
    {
    case LUP:
        if (m_StateTracker.leftStickUp == _buttonState)
            return true;
        break;
    case LDOWN:
        if (m_StateTracker.leftStickDown == _buttonState)
            return true;
        break;
    case LLEFT:
        if (m_StateTracker.leftStickLeft == _buttonState)
            return true;
        break;
    case LRIGHT:
        if (m_StateTracker.leftStickRight == _buttonState)
            return true;
        break;
    case RUP:
        if (m_StateTracker.rightStickUp == _buttonState)
            return true;
        break;
    case RDOWN:
        if (m_StateTracker.rightStickDown == _buttonState)
            return true;
        break;
    case RLEFT:
        if (m_StateTracker.rightStickLeft == _buttonState)
            return true;
        break;
    case RRIGHT:
        if (m_StateTracker.rightStickUp == _buttonState)
            return true;
        break;
    default:
        break;
    }
    return false;
}
