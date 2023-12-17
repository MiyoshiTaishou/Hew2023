#pragma once

#include"TakoyakiObject.h"

//‹ß‚Ã‚¢‚½‚ç“¦‚°‚é
class FakeTakoyakiObject : public TakoyakiObject
{
public:
	
	void Init();
	void Update();

private:

	//“¦‚°‚é‘¬“x
	float m_Speed = 25.0f;

	//‚Ç‚Ì‹——£‚©‚ç“¦‚°‚é‚©
	float m_EscapeLength = 50.0f;
};

