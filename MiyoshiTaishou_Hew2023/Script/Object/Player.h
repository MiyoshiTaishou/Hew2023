#pragma once
#include"gameObject.h"

enum PLAYERSTATE
{
	IDLE,
	HIT,
	NONE,
};

class Player : public GameObject
{
public:

	void Init();
	void Update();
	void Draw();

	//�����蔻�菈��
	void Collision();

	//�R���g���[���[����
	void ConInput();

private:

	PLAYERSTATE state = IDLE;

	//�ړ����x
	float m_Speed = 100.0f;

	//��]���x
	float m_RotSpeed = 150.0f;

	DirectX::SimpleMath::Vector3 torque;
};
