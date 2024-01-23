#pragma once

#include"../Object/gameObject.h"

//UI‚Ìó‘Ô‚ğŠÇ—‚·‚é
enum STATEUI
{

};

class HitUI : public GameObject
{
public:

	void Init();
	void Update();

private:

	GameObject* m_Hit[4];
	MATERIAL m_MT[4];
	STATEUI m_State[4];
};