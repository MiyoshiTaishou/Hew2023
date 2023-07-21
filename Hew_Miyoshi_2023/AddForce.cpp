#include "AddForce.h"
#include"gameObject.h"

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

	Vector3 pos = (this->m_GameObject->GetPosition() + velocity * deltaTime); // オブジェクトの位置を更新	

	this->m_GameObject->SetPosition(pos);
	force = Vector3(0.f, 0.f, 0.f); // 放置すると一生加速するので0に戻す
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
