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

	//パーティクル生成
	//引数、開始地点、方向
	void Create(DirectX::SimpleMath::Vector3 _pos,DirectX::SimpleMath::Vector3 _dir, DirectX::SimpleMath::Vector3 _speed);

private:

	//パーティクル数
	int m_ParticleCount = 1;

	//開始地点（プレイヤーの座標）
	DirectX::SimpleMath::Vector3 m_ParticleStartPos;	

	//振れ幅
	int m_Ampl = 10;	

	std::vector<ParticleObject*> m_Particle;
};