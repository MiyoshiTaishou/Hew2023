#pragma once
#include"gameObject.h"

#define MAX_SPHERE_MESH 14

enum PLAYERSTATE
{
	IDLE,
	HIT,
	NONE,
};

class SphereCollider;
class CMeshRenderer;
class CSphereMesh;
class Particle;

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

	DirectX::SimpleMath::Vector3 GetAfterPos()
	{
		return m_AfterPos;
	}

private:

	PLAYERSTATE state = IDLE;

	//移動速度
	float m_Speed = 70.0f;

	//加速度
	float m_Acc = 1.0f;

	//回転速度
	float m_RotSpeed = 0.0f;
	float m_RotSpeedSide = 0.0f;

	DirectX::SimpleMath::Quaternion accumulatedRotation = DirectX::SimpleMath::Quaternion::Identity;

	DirectX::SimpleMath::Vector3 torque;	

	std::vector<SphereCollider*> m_Collider;

	//球の表面の点
	DirectX::SimpleMath::Vector3 m_Point[MAX_SPHERE_MESH];

	//点の描画に使用する変数
	CMeshRenderer* m_MeshRenderer[MAX_SPHERE_MESH];
	CSphereMesh* m_Sphere[MAX_SPHERE_MESH];

	float m_Distance[MAX_SPHERE_MESH];

	Particle* m_Particle;
	
	DirectX::SimpleMath::Vector3 m_AfterPos;
};
