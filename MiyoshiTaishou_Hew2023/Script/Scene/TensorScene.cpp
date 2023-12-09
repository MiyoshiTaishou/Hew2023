#include "TensorScene.h"

//�I�u�W�F�N�g�֌W�w�b�_
#include"../Object/field.h"
#include"../Object/DebugCamera.h"
#include"../Object/BoxObject.h"

//�����蔻��
#include"../Component/SphereCollider.h"

//�R���|�[�l���g
#include"../Component/shader.h"
#include"../Component/RigidBody.h"

//ImGui
#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void TensorScene::Init()
{
	DebugCamera* camera = AddGameObject<DebugCamera>(Layer0);

	//AddGameObject<Field>(Layer1);

	/*sphere = AddGameObject<GameObject>(Layer1);
	RigidBody* body = sphere->AddComponent<RigidBody>();
	body->SetGravity(true);
	sphere->AddComponent<SphereCollider>()->SetRadius(2.0f);

	camera->m_TargetObj = sphere;*/

	box = AddGameObject<BoxObject>(Layer1);
	box->SetPosition(Vector3(10, 0, 0));
	box->AddComponent<RigidBody>();

	camera->m_TargetObj = box;
}

void TensorScene::Draw()
{	
	ImGui::Begin("RigidBody");

	ImGui::SliderFloat("TorqueX", &Torque.x, -10.0f, 10.0f);
	ImGui::SliderFloat("TorqueY", &Torque.y, -10.0f, 10.0f);
	ImGui::SliderFloat("TorqueZ", &Torque.z, -10.0f, 10.0f);

	ImGui::SliderFloat("SizeX", &scale.x, -10.0f, 10.0f);
	ImGui::SliderFloat("SizeY", &scale.y, -10.0f, 10.0f);
	ImGui::SliderFloat("SizeZ", &scale.z, -10.0f, 10.0f);

	//if (ImGui::Button("AddTorque"))
	//{
	//	//sphere->GetComponent<RigidBody>()->AddTorque(Torque, ForceMode::Acceleration);		
	//	box->GetComponent<RigidBody>()->AddTorque(Torque, ForceMode::Force);		
	//}

	if (ImGui::Button("Resset"))
	{
		//sphere->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		//box->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		box->SetScale(Vector3(1.0f, 1.0f, 1.0f));
	}

	if (ImGui::Button("SetSize"))
	{
		box->SetScale(scale);
	}

	ImGui::End();
}

void TensorScene::Update()
{
	/*Field* field = GetGameObject<Field>();

	Vector3 pos = box->GetPosition();	
	float height = field->GetFieldHeightBySqno(pos, *box);
	
	if (pos.y - 2.0f < height)
	{
		pos.y = height + 2.0f;

		box->SetPosition(pos);

		RigidBody* body = box->GetComponent<RigidBody>();

		Vector3 vel = body->GetVelocity();

		vel.y = 0.0f;

		body->SetVelocity(vel);
	}*/

	box->GetComponent<RigidBody>()->AddTorque(Torque, ForceMode::Force);
	box->GetComponent<RigidBody>()->SetInetiaTensorOfRectangular(scale.x, scale.y, scale.z , Vector3(0,0,0));
	box->SetScale(scale);
}
