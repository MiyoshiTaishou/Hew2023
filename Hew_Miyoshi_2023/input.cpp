#include "main.h"
#include <cstring> // for memset
#include "input.h"

using namespace DirectX;

/**
 * @brief キーボードの入力情報を管理するクラス
 */
BYTE Input::m_OldKeyState[256];
BYTE Input::m_KeyState[256];
DirectX::GamePad Input::m_GamePad;
DirectX::GamePad::ButtonStateTracker Input::m_StateTracker;
DirectX::GamePad::State Input::m_State;

/**
 * @brief Inputクラスの初期化
 */
void Input::Init()
{
    memset(m_OldKeyState, 0, 256);
    memset(m_KeyState, 0, 256);
}

/**
 * @brief キーボードとゲームパッドの入力情報の更新
 */
void Input::Update()
{
    memcpy(m_OldKeyState, m_KeyState, 256);
    GetKeyboardState(m_KeyState);

    m_State = m_GamePad.GetState(0);
    m_StateTracker.Update(m_State);
}

/**
 * @brief 指定されたキーコードのキーが押されているかを取得する
 * @param[in] KeyCode キーコード
 * @return キーが押されている場合はtrue、それ以外はfalse
 */
bool Input::GetKeyPress(BYTE KeyCode)
{
    return (m_KeyState[KeyCode] & 0x80);
}

/**
 * @brief 指定されたキーコードのキーが押された瞬間かを取得する
 * @param[in] KeyCode キーコード
 * @return キーが押された瞬間の場合はtrue、それ以外はfalse
 */
bool Input::GetKeyTrigger(BYTE KeyCode)
{
    return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

/**
 * @brief ゲームパッドのボタンの状態を取得する
 * @param[in] button ボタンの列挙型
 * @param[in] _buttonState ボタンの状態（UP/HELD/RELEASED/PRESSED）
 * @return ボタンの状態が指定されたものと一致する場合はtrue、それ以外はfalse
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
