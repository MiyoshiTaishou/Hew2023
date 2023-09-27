
#include "main.h"
#include "input.h"

using namespace DirectX;

//GamePad Input::m_GamePad;

//GamePad Input::m_GamePad;              /**< ゲームパッドのオブジェクト */
//GamePad::ButtonStateTracker Input::m_StateTracker;
//GamePad::State Input::m_State;
//

BYTE Input::m_OldKeyState[256];
BYTE Input::m_KeyState[256];

void Input::Init()
{

	memset( m_OldKeyState, 0, 256 );
	memset( m_KeyState, 0, 256 );	
	
}


void Input::Update()
{

	memcpy( m_OldKeyState, m_KeyState, 256 );

	GetKeyboardState( m_KeyState );	 

	/*m_State = m_GamePad.GetState(0);
	m_StateTracker.Update(m_State);	*/
}

bool Input::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

//bool Input::GetGamePad(BUTTON button, STATE _buttonState)
//{
//	switch (button)
//	{
//	case LUP:
//		if (m_StateTracker.leftStickUp == _buttonState)
//			return true;
//		break;
//	case LDOWN:
//		if (m_StateTracker.leftStickDown == _buttonState)
//			return true;
//		break;
//	case LLEFT:
//		if (m_StateTracker.leftStickLeft == _buttonState)
//			return true;
//		break;
//	case LRIGHT:
//		if (m_StateTracker.leftStickRight == _buttonState)
//			return true;
//		break;
//	case RUP:
//		if (m_StateTracker.rightStickUp == _buttonState)
//			return true;
//		break;
//	case RDOWN:
//		if (m_StateTracker.rightStickDown == _buttonState)
//			return true;
//		break;
//	case RLEFT:
//		if (m_StateTracker.rightStickLeft == _buttonState)
//			return true;
//		break;
//	case RRIGHT:
//		if (m_StateTracker.rightStickUp == _buttonState)
//			return true;
//		break;
//	default:
//		break;
//	}
//	return false;
//}
//
//void Input::Vibration(int player, float leftMotor, float rightMotor, float leftTrigger, float rightTrigger)
//{
//	m_GamePad.SetVibration(player, leftMotor, rightMotor, leftTrigger, rightTrigger);
//}
