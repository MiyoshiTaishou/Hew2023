#pragma once
#include "../Object/gameObject.h"

class Particle;

class YataiObject : public GameObject
{
private:	

	//パーティクル
	Particle* m_Particle;

	//パーティクルの出す量調整用
	int m_MoveCount = 0;
	int m_MaxMoveCount = 5;
	float m_CountScale;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};