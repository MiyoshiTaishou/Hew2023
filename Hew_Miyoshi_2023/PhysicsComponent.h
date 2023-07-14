#pragma once
#include "component.h"

class GameObject;

//ˆÚ“®‚Å‚«‚é‚æ‚¤‚É‚·‚é
class PhysicsComponent : public Component
{
public:
	using Component::Component;

	void Init();
	void Uninit() override;
	void Update();
	void Draw()override;

private:

	//‰‘¬“x
	float velocity = 0.1f;

	//‰Á‘¬“x
	float acc = 0.01f;

	//ŠÔ
	float time = 0.0f;

	//ÀÛ‚Ì‰Á‘¬“x
	float vel = 0;
};

