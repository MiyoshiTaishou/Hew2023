#pragma once
#include"gameObject.h"
#include"../Mesh/CMeshRenderer.h"
#include"../Mesh/CSphereMesh.h"
#include"../Component/BoundingSphere.h"

enum PLAYERSTATE
{
	IDLE,
	HIT,
	NONE,
};

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

	CMeshRenderer* m_MeshRenderer;
	CSphereMesh* m_Sphere;
	MATERIAL m_SphereMt;
	BoundingSphere m_Bs;
};
