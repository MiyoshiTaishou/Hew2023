#pragma once
#include "../Object/gameObject.h"

class ParticleObject : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	//透過するかどうか
	bool m_Fade = false;

	//進む方向
	DirectX::SimpleMath::Vector3 m_Dir;

	//パーティクル速度
	DirectX::SimpleMath::Vector3 m_Speed = { 0,50,0 };

	//パーティクルの終わる時間
	float m_LifeTime = 30.0f;

	float m_Alpha = 1.0f;

	float m_RotSpeed = 0.1f;

	bool m_DirRot = true;

	DirectX::SimpleMath::Vector3 m_ScaleColor;

public:
	void Init();
	void Init(const char* TextureName);
	void Uninit();
	void Draw();
	void Update();	

	void SetDir(DirectX::SimpleMath::Vector3 _dir) { m_Dir = _dir; }
	void SetSpeed(DirectX::SimpleMath::Vector3 _speed) { m_Speed = _speed; }
	void SetLifeTime(float _time) { m_LifeTime = _time; }
	void SetFade(bool _fade) { m_Fade = _fade; }

	DirectX::SimpleMath::Vector3 GetDir() { return m_Dir; }
	DirectX::SimpleMath::Vector3 GetSpeed() { return m_Speed; }
	float GetLifeTime() { return m_LifeTime; }

};