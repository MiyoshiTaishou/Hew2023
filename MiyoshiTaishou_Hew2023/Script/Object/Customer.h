#pragma once
#include"gameObject.h"
#include"../Component/animationModel.h"

class Customer : public GameObject
{
private:

	class AnimationModel* m_Model;
	int m_Frame;
	float m_BlendRate;

public:

	void Init() override;
	void Update() override;
	void PreDraw() override;
};