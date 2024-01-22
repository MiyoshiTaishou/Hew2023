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
	void Create(DirectX::SimpleMath::Vector3 _pos,DirectX::SimpleMath::Vector3 _dir, DirectX::SimpleMath::Vector3 _speed,float _lifeTime,bool _fade,float _scale);

	void SetTextureName(const char* _name) { m_TextureName = _name; }

private:

	//�p�[�e�B�N����
	int m_ParticleCount = 1;

	//�J�n�n�_�i�v���C���[�̍��W�j
	DirectX::SimpleMath::Vector3 m_ParticleStartPos;	

	//�U�ꕝ
	int m_Ampl = 10;	

	std::vector<ParticleObject*> m_Particle;

	std::string m_TextureName;
};