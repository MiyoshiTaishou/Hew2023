#include "PhysicsComponent.h"
#include"gameObject.h"
#include"input.h"
#include<SimpleMath.h>
#include"ImGuiManager.h"
#include"scene.h"
#include"manager.h"
#include"camera.h"

using namespace DirectX::SimpleMath;

void PhysicsComponent::Init()
{

}

void PhysicsComponent::Uninit()
{
}

void PhysicsComponent::Update()
{
	Scene* nowscene = Manager::GetScene();
	Camera* cameraObj = nowscene->GetGameObject<Camera>();

	Vector3 vec = m_GameObject->GetPosition();
	Vector3 fvec = cameraObj->GetForward();	
	Vector3 rot = m_GameObject->GetRotation();
	Vector3 camerarot = cameraObj->GetRotation();

	//等加速度運動
	float m = (velocity * time) + ((acc * (time * time)) / 2);	

	//加速の上限
	if (m > 0.5f)
		m = 0.5f;

	vel = m;

	Vector3 Vecm = Vector3(m, m, m);	

	//現在の位置を更新	
	if (Input::GetKeyPress('A'))
	{
		rot.y -= 1.0f / 60.0f;
	}
	if (Input::GetKeyPress('D'))
	{
		rot.y += 1.0f / 60.0f;
	}

	if (Input::GetKeyPress('W'))
	{
		rot.x += 5.0f / 60.f;
		vec += (fvec * Vecm);
	}

	if (Input::GetKeyPress('S'))
		vec -= (fvec * Vecm);	

	m_GameObject->SetPosition(vec);
	m_GameObject->SetRotation(rot);
	//cameraObj->SetRotation(camerarot);

	if (Input::GetKeyPress('W') || Input::GetKeyPress('S'))
	{
		time += 1.0f / 60.0f;
		return;
	}		

	time = 0;
}

void PhysicsComponent::Draw()
{
	ImGui::Begin("Physics");
	ImGui::Text("%f", vel);
	ImGui::End();
}
