#pragma once
#include<GamePad.h>

enum BUTTON
{
	LUP,
	LDOWN,
	LLEFT,
	LRIGHT,
	RUP,
	RDOWN,
	RLEFT,
	RRIGHT,
};

enum STATE
{
	UP = 0,         // Button is up
	HELD = 1,       // Button is held down
	RELEASED = 2,   // Button was just released
	PRESSED = 3,    // Buton was just pressed
};

class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];
	
	//ƒpƒbƒh‚Ì”»’è
	static DirectX::GamePad m_GamePad;
	static DirectX::GamePad::State m_State;
	static DirectX::GamePad::ButtonStateTracker m_StateTracker;
	
public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );

	static bool GetGamePad(BUTTON button,STATE _buttonState);	
};
