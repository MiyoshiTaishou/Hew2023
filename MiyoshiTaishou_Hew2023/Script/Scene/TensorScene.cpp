#include "TensorScene.h"

//オブジェクト関係ヘッダ
#include"../Object/field.h"
#include"../Object/DebugCamera.h"
#include"../Object/BoxObject.h"

//当たり判定
#include"../Component/SphereCollider.h"

//コンポーネント
#include"../Component/shader.h"
#include"../Component/RigidBody.h"

//ImGui
#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void TensorScene::Init()
{
	DebugCamera* camera = AddGameObject<DebugCamera>(Layer0);

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

	if (ImGui::Button("Resset"))
	{		
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
	box->GetComponent<RigidBody>()->AddTorque(Torque, ForceMode::Force);
	box->GetComponent<RigidBody>()->SetInetiaTensorOfRectangular(scale.x, scale.y, scale.z , Vector3(0,0,0));
	box->SetScale(scale);
}
