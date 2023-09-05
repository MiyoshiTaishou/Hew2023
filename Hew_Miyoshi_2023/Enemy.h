#pragma once
#include "gameObject.h"

//エネミープレイヤーに当たったらくっつく
class Enemy :  public GameObject
{
public:
	void Init()override;	
	void Update()override;
};

