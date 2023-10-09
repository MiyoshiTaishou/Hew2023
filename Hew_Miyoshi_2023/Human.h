#pragma once
#include "gameObject.h"
#include"animationModel.h"

//アニメーション付きの人
class Human : public GameObject
{
private:

	class AnimationModel* m_Model;
	int m_Frame;
	float m_BlendRate;

public:
	void Init() override;
	void Update() override;
	void Draw()override;
	void PreDraw() override;
};

