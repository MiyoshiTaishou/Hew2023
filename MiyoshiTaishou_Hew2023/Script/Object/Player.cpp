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

//描画
#include"../Render/modelRenderer.h"

//ImGui
#include"../ImGui/ImGuiManager.h"

//オブジェクト
#include"../Object/BoxObject.h"

using namespace DirectX::SimpleMath;

void Player::Init()
{
	//座標、サイズ設定
	this->m_Scale = Vector3(10.0f, 10.0f, 10.f);
	this->m_Position.x = 10.0f;
	this->m_Position.z = 0.0f;

	//コンポーネント
	//AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\vertexLightingPS.cso");
	//AddComponent<Shader>()->Load("../shader\\VS_GouraudShading.cso", "../shader\\PS_OrangeScale.cso");
	AddComponent<Shader>()->Load("../shader\\VS_Object.cso", "../shader\\PS_Toon.cso");
	ModelRenderer* model = AddComponent<ModelRenderer>();
	//model->Load("../asset\\model\\bullet.obj");
	model->Load("../asset\\model\\bullet.obj");

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
	//コントローラー入力
	ConInput();

	//当たり判定処理
	Collision();

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

	//ボックスとの当たり判定
	{
		std::vector<BoxObject*> boxlist = scene->GetGameObjects<BoxObject>();

		for (const auto& boxobj : boxlist)
		{			
			if (this->GetComponent<BoxCollider>()->Hit(boxobj->GetComponent<BoxCollider>()))
			{
				state = HIT;
			}
			else
			{
				state = IDLE;
			}
		}
	}
}

//入力処理
void Player::ConInput()
{
	if (Input::GetGamePad(BUTTON::LUP))
	{
		m_Position.z += 0.1f;
	}
	if (Input::GetGamePad(BUTTON::LDOWN))
	{
		m_Position.z -= 0.1f;
	}
	if (Input::GetGamePad(BUTTON::LLEFT))
	{
		m_Position.x -= 0.1f;
	}
	if (Input::GetGamePad(BUTTON::LRIGHT))
	{
		m_Position.x += 0.1f;
	}

	if (Input::GetGamePad(BUTTON::RRIGHT))
	{
		m_Rotation.y += 0.05f;
	}
	if (Input::GetGamePad(BUTTON::RLEFT))
	{
		m_Rotation.y += 0.05f;
	}
}
