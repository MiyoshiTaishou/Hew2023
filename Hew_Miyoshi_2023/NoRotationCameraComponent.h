#pragma once
#include "component.h"

//x���̉�]�̉e�����󂯂Ȃ�
class NoRotationCameraComponent :  public Component
{
public:
	using Component::Component;

	void Init();
	void Uninit() override;
	void Update();
};

