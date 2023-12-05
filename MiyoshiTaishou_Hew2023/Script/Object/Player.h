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
	DirectX::SimpleMath::Vector3 m_Point[6];

	//�_�̕`��Ɏg�p����ϐ�
	CMeshRenderer* m_MeshRenderer[6];
	CSphereMesh* m_Sphere[6];

	float m_Distance[6];
};
