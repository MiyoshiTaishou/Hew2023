#pragma once
#include "component.h"
#include<SimpleMath.h>

//�O���錾
class GameObject;

//�d�͂�����R���|�[�l���g
class Gravity : public Component
{
public:

	using Component::Component;

	void Update();

private:

	//�d�͂̋���
	DirectX::SimpleMath::Vector3 gravityPower = { 0,1,0 };

	//�d�͉����x
	float accGravity = 0.0098f;

	//����
	int time = 0;
};

