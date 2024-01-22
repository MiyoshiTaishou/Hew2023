#include "SlopeScene.h"

//オブジェクト関係ヘッダ
#include"../Object/field.h"
#include"../Object/DebugCamera.h"
#include"../Object/camera.h"

//当たり判定
#include"../Component/SphereCollider.h"

//コンポーネント
#include"../Component/shader.h"
#include"../Component/RigidBody.h"

//パーティクル
#include"../Particle/Particle.h"

//ImGui
#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void SlopeScene::Init()
{
	AddGameObject<Player>(Layer1);

	m_Particle = new Particle();
	m_Particle->SetTextureName("../asset/texture/Smoke.jpg");

	Field* filed = AddGameObject<Field>(Layer1);
	filed->Init("Title.csv");

	AddGameObject<Camera>(Layer0);
}

void SlopeScene::Uninit()
{
	m_Particle->Uninit();
}

void SlopeScene::Draw()
{
	ImGui::Begin("Particle");

	ImGui::SliderFloat("posX", &m_Pos.x, -100.0f, 100.0f);
	ImGui::SliderFloat("posY", &m_Pos.y, -100.0f, 100.0f);
	ImGui::SliderFloat("posZ", &m_Pos.z, -100.0f, 100.0f);

	ImGui::SliderFloat("DirX", &m_Dir.x, -10.0f, 10.0f);
	ImGui::SliderFloat("DirY", &m_Dir.y, -10.0f, 10.0f);
	ImGui::SliderFloat("DirZ", &m_Dir.z, -10.0f, 10.0f);

	ImGui::SliderFloat("SpeedX", &m_Speed.x, -10.0f, 10.0f);
	ImGui::SliderFloat("SpeedY", &m_Speed.y, -10.0f, 10.0f);
	ImGui::SliderFloat("SpeedZ", &m_Speed.z, -10.0f, 10.0f);

	ImGui::SliderFloat("Scale", &m_Scale, -10.0f, 10.0f);

	ImGui::SliderFloat("Life", &m_Life, 0.0f, 100.0f);

	ImGui::Checkbox("Fade", &m_Fade);

	ImGui::End();	
}

void SlopeScene::Update()
{
	m_Particle->Create(m_Pos, m_Dir, m_Speed, m_Life, m_Fade, m_Scale);
}
