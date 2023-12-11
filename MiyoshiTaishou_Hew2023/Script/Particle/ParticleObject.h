#pragma once
#include "../Object/gameObject.h"

class ParticleObject : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

public:
	void Init();
	void Uninit();
	void Draw();
	void Update();

	//進む方向
	DirectX::SimpleMath::Vector3 m_Dir;

	//パーティクルの終わる時間
	float m_LifeTime = 10.0f;

	float m_Alpha = 1.0f;
};