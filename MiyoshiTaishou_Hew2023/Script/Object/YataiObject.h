#pragma once
#include "../Object/gameObject.h"

class Particle;

class YataiObject : public GameObject
{
private:	

	//�p�[�e�B�N��
	Particle* m_Particle;

	//�p�[�e�B�N���̏o���ʒ����p
	int m_MoveCount = 0;
	int m_MaxMoveCount = 5;
	float m_CountScale;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};