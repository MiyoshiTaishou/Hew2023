#pragma once
#include "gameObject.h"

//デコボコの地面都の当たり判定用obj
//当たり判定ができないため今は意味がない
class Stage :   public GameObject
{
public:
	void Init() override;
	void Uninit()override;
};

