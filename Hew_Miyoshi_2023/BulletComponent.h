#pragma once
#include "component.h"
#include<SimpleMath.h>

//�e�𔭎˂��闭�߂̃R���|�[�l���g
class BulletComponent : public Component
{
public:
	using Component::Component;
	
	void Update();
	void Shot(DirectX::SimpleMath::Vector3 vec,GameObject &obj,DirectX::SimpleMath::Vector3 pos);
private:

	//��΂�����
	DirectX::SimpleMath::Vector3 shotVec;

	//���˂�����
	bool bShot = false;

	//���ԕϐ�
	float time = 0.0f;

	//���x
	float speed = 10.0f;
};

