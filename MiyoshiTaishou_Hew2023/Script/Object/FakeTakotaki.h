#pragma once

#include"TakoyakiObject.h"

//�߂Â����瓦����
class FakeTakoyakiObject : public TakoyakiObject
{
public:
	
	void Init();
	void Update();

private:

	//�����鑬�x
	float m_Speed = 25.0f;

	//�ǂ̋������瓦���邩
	float m_EscapeLength = 50.0f;
};

