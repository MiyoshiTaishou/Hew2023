#pragma once
#include<SimpleMath.h>
#include"ParticleObject.h"

class Particle
{
public:

	void Init();
	void Uninit();
	void Draw();
	void Update();

	//�p�[�e�B�N������
	//�����A�J�n�n�_�A����
	void Create(DirectX::SimpleMath::Vector3 _pos/*DirectX::SimpleMath::Vector3 _dir*/);

private:

	//�p�[�e�B�N����
	int m_ParticleCount = 1;

	//�J�n�n�_�i�v���C���[�̍��W�j
	DirectX::SimpleMath::Vector3 m_ParticleStartPos;

	//�p�[�e�B�N�����x
	DirectX::SimpleMath::Vector3 m_Speed = {0,20,0};

	//�U�ꕝ
	int m_Ampl = 10;	

	std::vector<ParticleObject*> m_Particle;
};