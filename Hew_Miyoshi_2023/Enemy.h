#pragma once
#include "gameObject.h"

//�G�l�~�[�v���C���[�ɓ��������炭����
class Enemy :  public GameObject
{
public:
	void Init()override;	
	void Update()override;
};

