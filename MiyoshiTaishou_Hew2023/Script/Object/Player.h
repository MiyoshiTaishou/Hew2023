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

	//�����蔻�菈��
	void Collision();

	//�R���g���[���[����
	void ConInput();

private:

	PLAYERSTATE state = IDLE;

	//�ړ����x
	float m_Speed = 100.0f;

	//��]���x
	float m_RotSpeed = 150.0f;

	DirectX::SimpleMath::Vector3 torque;

	CMeshRenderer* m_MeshRenderer;
	CSphereMesh* m_Sphere;
	MATERIAL m_SphereMt;
	BoundingSphere m_Bs;
};
