#include "SlopeScene.h"

//オブジェクト関係ヘッダ
#include"../Object/field.h"
#include"../Object/DebugCamera.h"

//当たり判定
#include"../Component/SphereCollider.h"

//コンポーネント
#include"../Component/shader.h"
#include"../Component/RigidBody.h"

//ImGui
#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void SlopeScene::Init()
{
	AddGameObject<DebugCamera>(Layer0);

	AddGameObject<Field>(Layer1);

	sphere = AddGameObject<GameObject>(Layer1);
	RigidBody* body = sphere->AddComponent<RigidBody>();
	body->SetGravity(true);
	sphere->AddComponent<SphereCollider>()->SetRadius(2.0f);
	/*sphere->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");*/
}

void SlopeScene::Draw()
{
	ImGui::Begin("RigidBody");

	ImGui::SliderFloat("posX", &force.x, -100.0f, 100.0f);
	ImGui::SliderFloat("posY", &force.y, -100.0f, 100.0f);
	ImGui::SliderFloat("posZ", &force.z, -100.0f, 100.0f);

	if (ImGui::Button("AddForce"))
	{
		sphere->GetComponent<RigidBody>()->AddForce(force, ForceMode::Impulse);
	}

	if (ImGui::Button("Resset"))
	{
		sphere->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	}

	ImGui::End();
}

void SlopeScene::Update()
{
	Field* field = GetGameObject<Field>();

	Vector3 pos = sphere->GetPosition();
	float height = field->GetFieldHeightBySqno(pos, *sphere);	

	if (pos.y - 2.0f < height)
	{
		pos.y = height + 2.0f;

		sphere->SetPosition(pos);

		RigidBody* body = sphere->GetComponent<RigidBody>();

		Vector3 vel = body->GetVelocity();

		vel.y = 0.0f;

		body->SetVelocity(vel);
	}	
}
