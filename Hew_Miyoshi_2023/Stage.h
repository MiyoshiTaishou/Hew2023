#pragma once
#include "gameObject.h"

//�f�R�{�R�̒n�ʓs�̓����蔻��pobj
//�����蔻�肪�ł��Ȃ����ߍ��͈Ӗ����Ȃ�
class Stage :   public GameObject
{
public:
	void Init() override;
	void Uninit()override;
};

