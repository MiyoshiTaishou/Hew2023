#pragma once
#include "gameObject.h"

//エネミー弾に当たったら消える
class Enemy :  public GameObject
{
public:
	void Init()override;	
	void Update()override;
};

