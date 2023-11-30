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
		m_Velocity.y -= gravity * m_Mass * m_GravityScale;
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
	//Rotをマトリックスに変換
	Matrix rotMatrix = Matrix::CreateFromYawPitchRoll(m_GameObject->GetRotation().y, m_GameObject->GetRotation().x, m_GameObject->GetRotation().z);

	//回転後の慣性テンソルを求める
	Matrix currentInetiaTensor = rotMatrix.Transpose() * m_InetiaTensor * rotMatrix;

	// Vector3をVector4に変換
	Vector4 torque4(m_Torque.x, m_Torque.y, m_Torque.z, 0.0f);

	//角加速度を求める
	Vector4 result4 = Vector4::Transform(torque4, currentInetiaTensor.Invert());

	// Vector4をVector3に戻す
	Vector3 angularAccel(result4.x, result4.y, result4.z);	

	//角速度を求める
	m_AngularVelocity = angularAccel + angularAccel * deltaTime;

	// 回転を更新
	Vector3 rot = m_GameObject->GetRotation();
	rot += m_AngularVelocity * deltaTime;
	m_GameObject->SetRotation(rot);

	//Vector3 frictionTorque = -m_AngularVelocity * m_AngularDrag;
	//Vector3 accelerationTorque = m_Torque / m_Mass;//加速度を計算
	//m_AngularVelocity = m_AngularVelocity + (accelerationTorque - frictionTorque) * deltaTime; // 速度を更新
	//
	////回転更新
	//Vector3 rot = m_GameObject->GetRotation();

	////XZの向きから回転を決める
	//float absX = fabsf(m_AngularVelocity.x);
	//float absZ = fabsf(m_AngularVelocity.z);
	//float addXZ = absX + absZ;		

	////後ろに回っているなら回転の向きを逆にする
	//if (m_BackRoll)
	//{
	//	addXZ *= -1;
	//}

	//rot.x += addXZ * deltaTime;

	//m_GameObject->SetRotation(m_AngularVelocity);

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

DirectX::SimpleMath::Vector3 RigidBody::GetVelocity()
{
	return m_Velocity;
}

void RigidBody::SetVelocity(DirectX::SimpleMath::Vector3 _vel)
{
	m_Velocity = _vel;
}

void RigidBody::SetFreeze(FrizeNum freez, bool _b)
{
}

float RigidBody::GetMass()
{
	return m_Mass;
}

void RigidBody::SetMass(float _mass)
{
	m_Mass = _mass;
}

void RigidBody::SetGravity(bool _gravity)
{
	m_UseGravity = _gravity;
}

void RigidBody::AddTorque(DirectX::SimpleMath::Vector3 _torque, ForceMode forceMode)
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
}

//慣性テンソルの設定
void RigidBody::SetInetiaTensorOfSpherAngular(float _radius, DirectX::SimpleMath::Vector3 _centerOfMass)
{
	float coefficient = (2.0f / 5.0f) * m_Mass * (_radius * _radius);

	Matrix tensor;

	tensor._11 = coefficient;
	tensor._12 = 0;
	tensor._13 = 0;
	tensor._14 = 0;

	tensor._21 = 0;
	tensor._22 = coefficient;
	tensor._23 = 0;
	tensor._24 = 0;

	tensor._31 = 0;
	tensor._32 = 0;
	tensor._33 = coefficient;
	tensor._34 = 0;

	tensor._41 = 0;
	tensor._42 = 0;
	tensor._43 = 0;
	tensor._44 = 1;

	m_InetiaTensor = tensor;
}

//二つの慣性テンソルを足す
void RigidBody::AddInetiaTensorOfSpherAngular(DirectX::SimpleMath::Matrix _InetiaTensor)
{
	m_InetiaTensor += _InetiaTensor;
}

DirectX::SimpleMath::Matrix RigidBody::GetInetiaTensor()
{
	return m_InetiaTensor;
}

void RigidBody::SetInetiaTensorOfRectangular(float x, float y, float z, DirectX::SimpleMath::Vector3 _centerOfMass)
{
	m_CenterOfMass = _centerOfMass;

	// 重心の慣性テンソルを計算
	float Ixx = -m_Mass * (m_CenterOfMass.y * m_CenterOfMass.y + m_CenterOfMass.z * m_CenterOfMass.z);
	float Iyy = -m_Mass * (m_CenterOfMass.x * m_CenterOfMass.x + m_CenterOfMass.z * m_CenterOfMass.z);
	float Izz = -m_Mass * (m_CenterOfMass.x * m_CenterOfMass.x + m_CenterOfMass.y * m_CenterOfMass.y);

	// 直方体の形状による慣性テンソルを計算
	float Ixx_rect = 1.0f / 12.0f * m_Mass * (y * y + z * z);
	float Iyy_rect = 1.0f / 12.0f * m_Mass * (x * x + z * z);
	float Izz_rect = 1.0f / 12.0f * m_Mass * (x * x + y * y);

	// 足し合わせる。慣性テンソルの対称性をうまく使って処理を効率化
	m_InetiaTensor._11 = Ixx + Ixx_rect;
	m_InetiaTensor._22 = Iyy + Iyy_rect;
	m_InetiaTensor._33 = Izz + Izz_rect;

	// 慣性テンソルの非対角成分はゼロ（直方体の場合）
	m_InetiaTensor._12 = m_InetiaTensor._21 = 0.0f;
	m_InetiaTensor._13 = m_InetiaTensor._31 = 0.0f;
	m_InetiaTensor._23 = m_InetiaTensor._32 = 0.0f;

	m_InetiaTensor._41 = 0;
	m_InetiaTensor._42 = 0;
	m_InetiaTensor._43 = 0;
	m_InetiaTensor._44 = 1;
}

void RigidBody::AddForceToPoint(Vector3 _force, Vector3 localPos, ForceMode forceMode)
{	
	Vector3 radius = localPos - m_CenterOfMass;
	Vector3 _torque = radius.Cross(_force);
	AddForce(_force, forceMode);
	AddTorque(_torque, forceMode);
}
