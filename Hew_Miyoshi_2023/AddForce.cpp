#include "AddForce.h"
#include"gameObject.h"
#include"ImGuiManager.h"

using namespace DirectX::SimpleMath;

void Rigidbody::Init(float _mass, float _drag,float _gravity)
{
	//初期値
	mass = _mass;
	drag = _drag;
	gravityScale = _gravity;
}

void Rigidbody::Update()
{			
	const float deltaTime = 1.f / 60.f; // 経過時間。固定フレームレートがよい。
	Vector3 friction = -velocity * drag;
	Vector3 acceleration = force / mass;//加速度を計算
	velocity = velocity + (acceleration - friction) * deltaTime; // 速度を更新

	//重力処理	
	const float gravity = 0.98f;
	velocity.y -= gravity * mass;
	
	if (mXPos)
		velocity.x = 0.0f;
	if (mYPos)
		velocity.y = 0.0f;
	if (mZPos)
		velocity.z = 0.0f;

	Vector3 pos = (this->m_GameObject->GetPosition() + velocity * deltaTime); // オブジェクトの位置を更新	
	Vector3 rot = (this->m_GameObject->GetRotation() + velocity * deltaTime); // オブジェクトの回転を更新	
	

	this->m_GameObject->SetPosition(pos);

	float forawrd = (rot.x + rot.z) * 0.9f;

	this->m_GameObject->SetRotation({ forawrd, this->m_GameObject->GetRotation().y,this->m_GameObject->GetRotation().y });
	force = Vector3(0.f, 0.f, 0.f); // 放置すると一生加速するので0に戻す
}

void Rigidbody::Draw()
{
	ImGui::Begin("Rigidbody");
	ImGui::Text("Velocity %f,%f,%f\n", velocity.x, velocity.y, velocity.z);
	ImGui::Text("Force %f,%f,%f\n", force.x, force.y, force.z);
	ImGui::End();
}

void Rigidbody::AddForce(DirectX::SimpleMath::Vector3 _force, ForceMode forceMode)
{
	const float deltaTime = 1.f / 60.f; // 経過時間
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

DirectX::SimpleMath::Vector3 Rigidbody::GetVelocity()
{
	return velocity;
}

void Rigidbody::SetVelocity(DirectX::SimpleMath::Vector3 _vel)
{
	velocity = _vel;
}

void Rigidbody::SetFreeze(Freeze freez,bool _b)
{
	switch (freez)
	{
	case Freeze::Xpos:
		mXPos = _b;
		break;
	case Freeze::YPos:
		mYPos = _b;
		break;
	case Freeze::ZPos:
		mZPos = _b;
		break;
	case Freeze::XRot:
		mXRot = _b;
		break;
	case Freeze::YRot:
		mYRot = _b;
		break;
	case Freeze::ZRot:
		mZRot = _b;
		break;
	default:
		break;
	}
}

bool Rigidbody::GetFreeze(Freeze freez)
{
	switch (freez)
	{
	case Freeze::Xpos:
		return mXPos;
		break;
	case Freeze::YPos:
		return mYPos;
		break;
	case Freeze::ZPos:
		return mZPos;
		break;
	case Freeze::XRot:
		return mXRot;
		break;
	case Freeze::YRot:
		return mYRot;
		break;
	case Freeze::ZRot:
		return mZRot;
		break;
	default:
		break;
	}

	return false;
}
