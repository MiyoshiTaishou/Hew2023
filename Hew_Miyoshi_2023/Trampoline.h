#pragma once
#include "gameObject.h"

//��ɏ��ƒ��˂�I�u�W�F�N�g
class Trampoline :  public GameObject
{
public:
	void Init() override;
	void Update()override;

	void SetPower(float _power);

	//���˂�
	void Action(GameObject* obj);
private:
	//���˂鋭��
	float power = 300.0f;
};

