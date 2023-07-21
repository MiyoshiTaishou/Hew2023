#include "AddForce.h"
#include"gameObject.h"

using namespace DirectX::SimpleMath;

void Rigidbody::Init(float _mass, float _drag,float _gravity)
{
	//�����l
	mass = _mass;
	drag = _drag;
	gravityScale = _gravity;
}

void Rigidbody::Update()
{		
	const float deltaTime = 1.f / 60.f; // �o�ߎ��ԁB�Œ�t���[�����[�g���悢�B
	Vector3 friction = -velocity * drag;
	Vector3 acceleration = force / mass;//�����x���v�Z
	velocity = velocity + (acceleration - friction) * deltaTime; // ���x���X�V

	//�d�͏���
	const float gravity = 0.98f;
	velocity.y -= gravity * mass;

	Vector3 pos = (this->m_GameObject->GetPosition() + velocity * deltaTime); // �I�u�W�F�N�g�̈ʒu���X�V	

	this->m_GameObject->SetPosition(pos);
	force = Vector3(0.f, 0.f, 0.f); // ���u����ƈꐶ��������̂�0�ɖ߂�
}

void Rigidbody::AddForce(DirectX::SimpleMath::Vector3 _force, ForceMode forceMode)
{
	const float deltaTime = 1.f / 60.f; // �o�ߎ���
	switch (forceMode)
	{
	case ForceMode::Force:
		force = force + _force;
		break;
	case ForceMode::Impuluse:
		force = force + (_force / deltaTime);
		break;
	}
}
