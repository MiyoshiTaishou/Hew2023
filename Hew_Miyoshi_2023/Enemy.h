#pragma once
#include "gameObject.h"

//�G�l�~�[�e�ɓ��������������
class Enemy :  public GameObject
{
public:
	void Init()override;	
	void Update()override;
};

