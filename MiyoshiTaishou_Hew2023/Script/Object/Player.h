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

	//�����蔻�菈��
	void Collision();

	//�R���g���[���[����
	void ConInput();

	DirectX::SimpleMath::Vector3 GetAfterPos()
	{
		return m_AfterPos;
	}

private:

	PLAYERSTATE state = IDLE;

	//�ړ����x
	float m_Speed = 70.0f;

	//�����x
	float m_Acc = 1.0f;

	//��]���x
	float m_RotSpeed = 0.0f;
	float m_RotSpeedSide = 0.0f;

	DirectX::SimpleMath::Quaternion accumulatedRotation = DirectX::SimpleMath::Quaternion::Identity;

	DirectX::SimpleMath::Vector3 torque;	

	std::vector<SphereCollider*> m_Collider;

	//���̕\�ʂ̓_
	DirectX::SimpleMath::Vector3 m_Point[MAX_SPHERE_MESH];

	//�_�̕`��Ɏg�p����ϐ�
	CMeshRenderer* m_MeshRenderer[MAX_SPHERE_MESH];
	CSphereMesh* m_Sphere[MAX_SPHERE_MESH];

	float m_Distance[MAX_SPHERE_MESH];

	Particle* m_Particle;
	
	DirectX::SimpleMath::Vector3 m_AfterPos;
};
