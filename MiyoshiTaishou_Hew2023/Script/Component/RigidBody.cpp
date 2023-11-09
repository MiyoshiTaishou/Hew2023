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
	//力処理
	const float deltaTime = 1.f / 60.f; // 経過時間。固定フレームレートがよい。
	Vector3 friction = -m_Velocity * m_Drag;
	Vector3 acceleration = m_Force / m_Mass;//加速度を計算
	m_Velocity = m_Velocity + (acceleration - friction) * deltaTime; // 速度を更新

	//重力処理
	if (m_UseGravity)
	{
		const float gravity = 0.98f;
		//m_Velocity.y -= gravity * m_Mass * m_GravityScale;
	}

	//固定化されているなら計算を無効にする
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

	m_Force = Vector3(0.f, 0.f, 0.f); // 放置すると一生加速するので0に戻す


	//座標更新
	Vector3 pos = m_GameObject->GetPosition();	
	pos += m_Velocity * deltaTime;
	m_GameObject->SetPosition(pos);	

	//回転処理
	Vector3 frictionTorque = -m_AngularVelocity * m_AngularDrag;
	Vector3 accelerationTorque = m_Torque / m_Mass;//加速度を計算
	m_AngularVelocity = m_AngularVelocity + (accelerationTorque - frictionTorque) * deltaTime; // 速度を更新
	
	//回転更新
	Vector3 rot = m_GameObject->GetRotation();

	//XZの向きから回転を決める
	float absX = fabsf(m_AngularVelocity.x);
	float absZ = fabsf(m_AngularVelocity.z);
	float addXZ = absX + absZ;		

	//後ろに回っているなら回転の向きを逆にする
	if (m_BackRoll)
	{
		addXZ *= -1;
	}

	rot.x += addXZ * deltaTime;

	m_GameObject->SetRotation(rot);

	m_Torque = Vector3(0.f, 0.f, 0.f); // 放置すると一生加速するので0に戻す
}

void RigidBody::Draw()
{
	//値確認用
	ImGui::Begin("Rigidbody");
	ImGui::Text("Velocity %f,%f,%f\n", m_Velocity.x, m_Velocity.y, m_Velocity.z);
	ImGui::Text("Torque %f,%f,%f\n", m_AngularVelocity.x, m_AngularVelocity.y, m_AngularVelocity.z);
	ImGui::End();
}

void RigidBody::AddForce(DirectX::SimpleMath::Vector3 _force, ForceMode forceMode)
{	
	const float deltaTime = 1.f / 60.f; // 経過時間

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
	const float deltaTime = 1.f / 60.f; // 経過時間。固定フレームレートがよい。

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
