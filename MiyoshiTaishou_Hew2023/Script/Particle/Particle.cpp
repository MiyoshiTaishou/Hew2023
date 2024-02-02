#include "Particle.h"

//コンポーネント
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
			delete obj;			
		}
	}

}

void Particle::Draw()
{
	// 加算合成
	Renderer::SetDepthEnable(false);
	
	for (auto* obj : m_Particle)
	{
		if (obj != nullptr)
		{
			obj->DrawBase(Matrix::Identity);
		}
	}

	Renderer::SetDepthEnable(true);
}

void Particle::Update()
{
	for (int i = 0; i < m_Particle.size(); i++)
	{
		auto* obj = m_Particle[i];

		if (obj != nullptr)
		{			
			obj->UpdateBase();

			if (obj->GetLifeTime() == 0)
			{
				obj->UninitBase();
				delete obj;
				m_Particle.erase(m_Particle.begin() + i);				
			}
		}
	}
}

void Particle::Create(DirectX::SimpleMath::Vector3 _pos, DirectX::SimpleMath::Vector3 _dir, DirectX::SimpleMath::Vector3 _speed, float _lifeTime, bool _fade,float _scale)
{
	//パーティクルの生成
	for (int i = 0; i < m_ParticleCount; i++)
	{
		ParticleObject* obj = new ParticleObject();
		obj->Init(m_TextureName.c_str());

		//位置と進む方向を設定		
		float randDirX = rand() % m_Ampl * 0.1f;
		float randDirZ = rand() % m_Ampl * 0.1f;
		Vector3 Dir = Vector3(randDirX, 1, randDirZ);

		obj->SetDir(Dir);
		obj->SetSpeed(_speed);
		obj->SetFade(_fade);
		obj->SetLifeTime(_lifeTime);
		obj->SetScale(Vector3(_scale, 0, 0));

		float randPosX = rand() % m_Ampl * 0.5f;
		float randPosZ = rand() % m_Ampl * 0.5f;

		Vector3 Pos = Vector3(randPosX + _pos.x, _pos.y, randPosZ + _pos.z);

		obj->SetPosition(Pos);

		m_Particle.push_back(obj);
	}
}