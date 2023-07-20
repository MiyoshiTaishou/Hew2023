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
};

