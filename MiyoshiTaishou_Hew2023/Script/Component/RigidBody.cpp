#include "RigidBody.h"

#include"../Object/gameObject.h"

#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void RigidBody::Init()
{
	m_Frize.Xpos = false;
	m_Frize.YPos = false;
	m_Frize.ZPos = false;
	m_Frize.XRot = false;	
	m_Frize.YRot = false;	
	m_Frize.ZRot = false;	
}

void RigidBody::Update()
{	
	//�͏���
	const float deltaTime = 1.f / 60.f; // �o�ߎ��ԁB�Œ�t���[�����[�g���悢�B
	Vector3 friction = -m_Velocity * m_Drag;
	Vector3 acceleration = m_Force / m_Mass;//�����x���v�Z
	m_Velocity = m_Velocity + (acceleration - friction) * deltaTime; // ���x���X�V

	//�d�͏���
	if (m_UseGravity)
	{
		const float gravity = 0.98f;
		//m_Velocity.y -= gravity * m_Mass * m_GravityScale;
	}

	//�Œ艻����Ă���Ȃ�v�Z�𖳌��ɂ���
	if (m_Frize.Xpos)
	{
		m_Velocity.x = 0.0f;
	}
	if (m_Frize.YPos)
	{
		m_Velocity.y = 0.0f;
	}
	if (m_Frize.ZPos)
	{
		m_Velocity.z = 0.0f;
	}

	m_Force = Vector3(0.f, 0.f, 0.f); // ���u����ƈꐶ��������̂�0�ɖ߂�


	//���W�X�V
	Vector3 pos = m_GameObject->GetPosition();	
	pos += m_Velocity * deltaTime;
	m_GameObject->SetPosition(pos);	

	//��]����
	Vector3 frictionTorque = -m_AngularVelocity * m_AngularDrag;
	Vector3 accelerationTorque = m_Torque / m_Mass;//�����x���v�Z
	m_AngularVelocity = m_AngularVelocity + (accelerationTorque - frictionTorque) * deltaTime; // ���x���X�V
	
	//��]�X�V
	Vector3 rot = m_GameObject->GetRotation();

	//XZ�̌��������]�����߂�
	float absX = fabsf(m_AngularVelocity.x);
	float absZ = fabsf(m_AngularVelocity.z);
	float addXZ = absX + absZ;		

	//���ɉ���Ă���Ȃ��]�̌������t�ɂ���
	if (m_BackRoll)
	{
		addXZ *= -1;
	}

	rot.x += addXZ * deltaTime;

	m_GameObject->SetRotation(rot);

	m_Torque = Vector3(0.f, 0.f, 0.f); // ���u����ƈꐶ��������̂�0�ɖ߂�
}

void RigidBody::Draw()
{
	//�l�m�F�p
	ImGui::Begin("Rigidbody");
	ImGui::Text("Velocity %f,%f,%f\n", m_Velocity.x, m_Velocity.y, m_Velocity.z);
	ImGui::Text("Torque %f,%f,%f\n", m_AngularVelocity.x, m_AngularVelocity.y, m_AngularVelocity.z);
	ImGui::End();
}

void RigidBody::AddForce(DirectX::SimpleMath::Vector3 _force, ForceMode forceMode)
{	
	const float deltaTime = 1.f / 60.f; // �o�ߎ���

	switch (forceMode)
	{
	case ForceMode::Force:
		m_Force = m_Force + _force;
		break;
	case ForceMode::Acceleration:
		m_Force = m_Force + (_force * m_Mass);
			break;
	case ForceMode::Impulse:
		m_Force = m_Force + (_force / deltaTime);
		break;		
	case ForceMode::VelocityChange:
		m_Force = m_Force + ((_force / deltaTime) * m_Mass);
	}
}

void RigidBody::SetFreeze(FrizeNum freez, bool _b)
{
}

void RigidBody::AddTorque(DirectX::SimpleMath::Vector3 _torque, ForceMode forceMode, bool _back)
{
	const float deltaTime = 1.f / 60.f; // �o�ߎ��ԁB�Œ�t���[�����[�g���悢�B

	switch (forceMode)
	{
	case ForceMode::Force:
		m_Torque = m_Torque + _torque;
		break;
	case ForceMode::Acceleration:
		m_Torque = m_Torque + (_torque * m_Mass);
		break;
	case ForceMode::Impulse:
		m_Torque = m_Torque + (_torque / deltaTime);
		break;
	case ForceMode::VelocityChange:
		m_Torque = m_Torque + ((_torque / deltaTime) * m_Mass);
	}

	m_BackRoll = _back;
}
