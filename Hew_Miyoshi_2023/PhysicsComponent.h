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
};

