#pragma once
#include "component.h"

class GameObject;

//�ړ��ł���悤�ɂ���
class PhysicsComponent : public Component
{
public:
	using Component::Component;

	void Init();
	void Uninit() override;
	void Update();
	void Draw()override;

private:

	//�����x
	float velocity = 0.1f;

	//�����x
	float acc = 0.01f;

	//����
	float time = 0.0f;

	//���ۂ̉����x
	float vel = 0;
};

