#pragma once
#include "gameObject.h"
class Stage :   public GameObject
{
public:
	void Init() override;
	void Uninit()override;
};

