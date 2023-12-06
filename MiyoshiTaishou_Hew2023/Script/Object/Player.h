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

	std::vector<SphereCollider*> m_Collider;

	//���̕\�ʂ̓_
	DirectX::SimpleMath::Vector3 m_Point[MAX_SPHERE_MESH];

	//�_�̕`��Ɏg�p����ϐ�
	CMeshRenderer* m_MeshRenderer[MAX_SPHERE_MESH];
	CSphereMesh* m_Sphere[MAX_SPHERE_MESH];

	float m_Distance[MAX_SPHERE_MESH];
};
