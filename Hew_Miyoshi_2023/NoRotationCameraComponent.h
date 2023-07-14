#pragma once
#include "component.h"

//xŽ²‚Ì‰ñ“]‚Ì‰e‹¿‚ðŽó‚¯‚È‚¢
class NoRotationCameraComponent :  public Component
{
public:
	using Component::Component;

	void Init();
	void Uninit() override;
	void Update();
};

