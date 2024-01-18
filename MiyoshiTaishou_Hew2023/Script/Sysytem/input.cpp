
#include "main.h"
#include "input.h"

using namespace DirectX;

BYTE Input::m_OldKeyState[256];
BYTE Input::m_KeyState[256];
//DirectX::GamePad Input::m_GamePad;
//DirectX::GamePad::ButtonStateTracker Input::m_StateTracker;
//DirectX::GamePad::State Input::m_State;

XINPUT_STATE Input::m_ControllerState; // コントローラーの状態を保持する変数
XINPUT_STATE Input::m_OldControllerState;

void Input::Init()
{
    memset(m_OldKeyState, 0, 256);
    memset(m_KeyState, 0, 256);
    ZeroMemory(&m_ControllerState, sizeof(XINPUT_STATE)); // コントローラーの状態を初期化
}

void Input::Update()
{
    memcpy(m_OldKeyState, m_KeyState, 256);
    m_OldControllerState = m_ControllerState;
    GetKeyboardState(m_KeyState);

    // コントローラーの状態を取得
    DWORD result = XInputGetState(0, &m_ControllerState);

    // コントローラーが接続されているか確認
    if (result != ERROR_SUCCESS)
    {
        ZeroMemory(&m_ControllerState, sizeof(XINPUT_STATE)); // コントローラーが接続されていない場合、状態をクリア
    }
}

bool Input::GetKeyPress(BYTE KeyCode)
{
    return (m_KeyState[KeyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE KeyCode)
{
    return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

bool Input::GetGamePad(BUTTON button)
{
    // コントローラーのボタンの状態をチェック
    switch (button)
    {
    case BUTTON::LUP:
        return (m_ControllerState.Gamepad.sThumbLY > 0);
    case BUTTON::LDOWN:
        return (m_ControllerState.Gamepad.sThumbLY < 0);
    case BUTTON::LLEFT:
        return (m_ControllerState.Gamepad.sThumbLX < 0);
    case BUTTON::LRIGHT:
        return (m_ControllerState.Gamepad.sThumbLX > 0);
    case BUTTON::RUP:
        return (m_ControllerState.Gamepad.sThumbRY > 0);
    case BUTTON::RDOWN:                                                         
        return (m_ControllerState.Gamepad.sThumbRY < 0);
    case BUTTON::RLEFT:                                                         
        return (m_ControllerState.Gamepad.sThumbRX < 0);
    case BUTTON::RRIGHT:                                                        
        return (m_ControllerState.Gamepad.sThumbRX > 10000);
    case BUTTON::ABUTTON:
        return (m_ControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A);
    default:
        break;
    }
    return false;
}

bool Input::GetGamePadTrigger(BUTTON button)
{
    switch (button)
    {
    case BUTTON::LUP:
        return (m_ControllerState.Gamepad.sThumbLY > 0) && !(m_OldControllerState.Gamepad.sThumbLY > 0);
    case BUTTON::LDOWN:
        return (m_ControllerState.Gamepad.sThumbLY < 0) && !(m_OldControllerState.Gamepad.sThumbLY < 0);        
    case BUTTON::ABUTTON:
        return (m_ControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A) && !(m_OldControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A);
    case BUTTON::BBUTTON:
        return(m_ControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B) && !(m_OldControllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B);
    default:
        break;
    }
    return false;
}


void Input::Vibration(int player, float leftMotor, float rightMotor, float leftTrigger, float rightTrigger)
{
    // コントローラーの振動を設定
    XINPUT_VIBRATION vibration;
    ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
    vibration.wLeftMotorSpeed = static_cast<WORD>(leftMotor * 65535.0f);
    vibration.wRightMotorSpeed = static_cast<WORD>(rightMotor * 65535.0f);
   /* vibration.bLeftTrigger = static_cast<BYTE>(leftTrigger * 255);
    vibration.bRightTrigger = static_cast<BYTE>(rightTrigger * 255);*/
    XInputSetState(player, &vibration);
}