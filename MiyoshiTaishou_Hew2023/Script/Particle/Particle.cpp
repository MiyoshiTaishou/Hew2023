#include "Particle.h"

//�R���|�[�l���g
#include"../Component/RigidBody.h"

using namespace DirectX::SimpleMath;

void Particle::Init()
{
}

void Particle::Uninit()
{
	for (auto* obj : m_Particle)
	{
		if (obj != nullptr)
		{
			obj->UninitBase();
		}
	}

}

void Particle::Draw()
{
	for (auto* obj : m_Particle)
	{
		if (obj != nullptr)
		{
			obj->DrawBase(Matrix::Identity);
		}
	}
}

void Particle::Update()
{
	for (int i = 0; i < m_Particle.size(); i++)
	{
		auto* obj = m_Particle[i];

		if (obj != nullptr)
		{
			RigidBody* body = obj->GetComponent<RigidBody>();

			Vector3 power = obj->m_Dir * m_Speed;
			body->AddForce(power, ForceMode::Acceleration);

			obj->UpdateBase();

			if (obj->m_LifeTime == 0)
			{
				obj->UninitBase();
				delete obj;
				m_Particle.erase(m_Particle.begin() + i);				
			}
		}
	}
}

void Particle::Create(DirectX::SimpleMath::Vector3 _pos /*DirectX::SimpleMath::Vector3 _dir*/)
{
	//�p�[�e�B�N���̐���
	for (int i = 0; i < m_ParticleCount; i++)
	{
		ParticleObject* obj = new ParticleObject();
		obj->InitBase();

		//�ʒu�Ɛi�ޕ�����ݒ�		
		float randDirX = rand() % m_Ampl * 0.1f;
		float randDirZ = rand() % m_Ampl * 0.1f;
		Vector3 Dir = Vector3(randDirX, 1, randDirZ);

		obj->m_Dir = Dir;

		float randPosX = rand() % m_Ampl * 0.5f;
		float randPosZ = rand() % m_Ampl * 0.5f;

		Vector3 Pos = Vector3(randPosX + _pos.x, _pos.y, randPosZ + _pos.z);

		obj->SetPosition(Pos);

		m_Particle.push_back(obj);
	}	
}
