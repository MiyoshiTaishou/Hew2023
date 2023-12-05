#pragma once
#include"gameObject.h"

enum PLAYERSTATE
{
	IDLE,
	HIT,
	NONE,
};

class SphereCollider;
class CMeshRenderer;
class CSphereMesh;

class Player : public GameObject
{
public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

	//当たり判定処理
	void Collision();

	//コントローラー入力
	void ConInput();

private:

	PLAYERSTATE state = IDLE;

	//移動速度
	float m_Speed = 100.0f;

	//回転速度
	float m_RotSpeed = 150.0f;

	DirectX::SimpleMath::Vector3 torque;	

	std::vector<SphereCollider*> m_Collider;

	//球の表面の点
	DirectX::SimpleMath::Vector3 m_Point[6];

	//点の描画に使用する変数
	CMeshRenderer* m_MeshRenderer[6];
	CSphereMesh* m_Sphere[6];

	float m_Distance[6];
};
