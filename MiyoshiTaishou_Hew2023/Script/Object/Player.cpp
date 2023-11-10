#include<SimpleMath.h>

#include "Player.h"

//管理
#include"../Sysytem/manager.h"

//シーン
#include"../Scene/scene.h"

//入力
#include"../Sysytem/input.h"

//コンポーネント
#include"../Component/shader.h"
#include"../Component/BoxCollider.h"
#include"../Component/RigidBody.h"
#include"../Component/shadow.h"

//描画
#include"../Render/modelRenderer.h"

//ImGui
#include"../ImGui/ImGuiManager.h"

//オブジェクト
#include"BoxObject.h"
#include"camera.h"
#include"field.h"

using namespace DirectX::SimpleMath;

void Player::Init()
{
	//座標、サイズ設定
	this->m_Scale = Vector3(10.0f, 10.0f, 10.f);
	this->m_Position.x = 10.0f;
	this->m_Position.z = 0.0f;

	//コンポーネント
	//AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\vertexLightingPS.cso");
	AddComponent<Shader>()->Load("../shader\\VS_GouraudShading.cso", "../shader\\PS_OrangeScale.cso");
	//AddComponent<Shader>()->Load("../shader\\VS_Object.cso", "../shader\\PS_Toon.cso");
	

	ModelRenderer* model = AddComponent<ModelRenderer>();
	//model->Load("../asset\\model\\bullet.obj");
	model->Load("../asset\\model\\bullet.obj");

	Shadow* shadow = AddComponent<Shadow>();
	shadow->Init();
	shadow->SetSize(10.0f);

	AddComponent<RigidBody>()->Init();

	//当たり判定の大きさをオブジェクトに合わせる
	Vector3 absModelScale;
	absModelScale.x = fabsf(ModelRenderer::Max.x) + fabsf(ModelRenderer::Min.x);
	absModelScale.y = fabsf(ModelRenderer::Max.y) + fabsf(ModelRenderer::Min.y);
	absModelScale.z = fabsf(ModelRenderer::Max.z) + fabsf(ModelRenderer::Min.z);

	BoxCollider* box = AddComponent<BoxCollider>();
	box->Init();
	box->SetColliderScale((absModelScale * m_Scale));
}

void Player::Update()
{	
	//当たり判定処理
	Collision();

	//コントローラー入力
	ConInput();

	//コンポーネントのUpdate呼び出し
	for (auto& cmpt : m_Component) {
		cmpt->Update();
	}
}

void Player::Draw()
{
	//プレイヤーの情報を表示する
	ImGui::Begin("Player");
	ImGui::Text("PlayerScale\n %f\nY %f\nZ %f", this->m_Scale.x, this->m_Scale.y, this->m_Scale.z);
	ImGui::Text("PlayerPos\nX %f\nY %f\nZ %f", this->m_Position.x, this->m_Position.y, this->m_Position.z);
	ImGui::Text("PlayerRot\nX %f\nY %f\nZ %f", this->m_Rotation.x, this->m_Rotation.y, this->m_Rotation.z);
	ImGui::Text("PlayerFow\nX %f\nY %f\nZ %f", this->GetForward().x, this->GetForward().y, this->GetForward().z);
	ImGui::Text("PlayerState\n %d", this->state);
	ImGui::End();
}

void Player::Collision()
{
	// 現在シーンを取得
	Scene* scene = Manager::GetScene();	

	//くっつくオブジェクト当たり判定
	{
		std::vector<BoxObject*> boxlist = scene->GetGameObjects<BoxObject>();

		for (const auto& boxobj : boxlist)
		{			
			if (this->GetComponent<BoxCollider>()->Hit(boxobj->GetComponent<BoxCollider>()))
			{
				//くっつく処理
				StickObject* child = AddChild<BoxObject>();				
				child->Stick();						

				//オブジェクト削除
				boxobj->SetDestroy();

				state = HIT;
			}
			else
			{
				state = IDLE;
			}
		}
	}
	
	//高さを取得	
	float Height = scene->GetGameObject<Field>()->GetFieldHeight(m_Position);
	
	if (Height != 0.0f)
	{
		//pos.y = Height;
		m_Position.y = Height + 2;
	}	
}

//入力処理
void Player::ConInput()
{
	// 現在シーンを取得
	Scene* scene = Manager::GetScene();

	Camera* cameraObj = scene->GetGameObject<Camera>();

	RigidBody* body = GetComponent<RigidBody>();

	//カメラの前向きベクトル
	Vector3 forward = Vector3(0, 0, 0);	
	if (cameraObj)
	{
		forward = cameraObj->GetForward();
	}

	if (Input::GetGamePad(BUTTON::LUP))
	{
		Vector3 force = forward * 100.0f;
		Vector3 forceRot = forward * 10.0f;

		body->AddForce(force, ForceMode::Force);
		body->AddTorque(forceRot, ForceMode::Force,false);
	}
	if (Input::GetGamePad(BUTTON::LDOWN))
	{
		Vector3 force = forward * -100.0f;
		Vector3 forceRot = forward * -10.0f;
		body->AddForce(force, ForceMode::Force);
		body->AddTorque(forceRot, ForceMode::Force,true);
	}
	/*if (Input::GetGamePad(BUTTON::LLEFT))
	{
		m_Position.x -= 0.1f;
	}
	if (Input::GetGamePad(BUTTON::LRIGHT))
	{
		m_Position.x += 0.1f;
	}*/

	if (Input::GetGamePad(BUTTON::RRIGHT))
	{
		m_Rotation.y += 0.05f;
	}
	if (Input::GetGamePad(BUTTON::RLEFT))
	{
		m_Rotation.y -= 0.05f;
	}

	if (Input::GetKeyTrigger('J'))
	{
		Vector3 force = { 0,100,0 };
		body->AddForce(force, ForceMode::Impulse);
	}
}
