#pragma once
#include "component.h"
#include<GamePad.h>

enum Button
{
	LeftStickUp,
	LeftStickDown,
	LeftStickRight,
	LeftStickLeft,
	RightStickUp,
	RightStickDown,
	RightStickRight,
	RightStickLeft,
};

class GamePadComponent :  public Component
{
public:
	using Component::Component;
	
	void Update() override;	
private:	
	DirectX::GamePad::ButtonStateTracker m_StateTracker;
};

