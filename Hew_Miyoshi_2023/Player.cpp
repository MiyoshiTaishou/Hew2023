#include<SimpleMath.h>
#include "Player.h"
#include"modelRenderer.h"
#include"shader.h"
#include"PhysicsComponent.h"
#include"JumpComponent.h"
#include"BoxCollider.h"
#include"audio.h"
#include"scene.h"
#include"manager.h"
#include"Goal.h"
#include"collison.h"
#include"input.h"
#include"Bullet.h"
#include"box.h"
#include"camera.h"

#include"ImGuiManager.h"

using namespace DirectX::SimpleMath;

void Player::Init()
{			
	AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");
	//AddComponent<ModelRenderer>()->Load("asset\\model\\bullet.obj");
	m_VertexPos =  AddComponent<ModelRenderer>()->LoadVertex("asset\\model\\bullet.obj");	
	AddComponent<PhysicsComponent>()->Init();		
	AddComponent<JumpComponent>()->Init();				

	this->m_Scale *= 10;
	this->m_Position.y = 10.0f;
	this->m_Position.x = 10.0f;		

	m_SE = AddComponent<Audio>();
	m_SE->Load("asset\\audio\\wan.wav");

	//m_Size=
}

void Player::Uninit()
{
	
}


void Player::Update()
{	


	for (auto& cmpt : m_Component) {
		cmpt->Update();
	}	

	// 現在シーンを取得
	Scene* scene = Manager::GetScene();

	// ゴールとの当たり判定
	{
		Goal* goal = scene->GetGameObject<Goal>();
		//std::vector<Goal*> goal = scene->GetGameObjects<Goal>();

		if (goal)
		{
			Vector3 position = goal->GetPosition();
			Vector3 scale = goal->GetScale();

			// ゴールのAABB作成
			AABB aabbGoal;
			Vector3 GoalSize(2.0f, 2.0f, 2.0f);
			aabbGoal = SetAABB(
				position,
				fabs(GoalSize.x * scale.x),
				fabs(GoalSize.y * scale.y),
				fabs(GoalSize.z * scale.z));

			// プレイヤのAABB作成
			AABB aabbPlayer;
			Vector3 PlayerSize(1.0f, 2.0f, 1.0f);
			aabbPlayer = SetAABB(
				Vector3(m_Position.x, m_Position.y + 1.0f, m_Position.z),
				fabs(PlayerSize.x * m_Scale.x),
				fabs(PlayerSize.y * m_Scale.y),
				fabs(PlayerSize.z * m_Scale.z));

			// AABB当たり判定
			bool sts = CollisionAABB(aabbPlayer, aabbGoal);

			if (sts)
			{
				goal->SetDestroy();
			}
		}

	}

	//Boxの当たり判定
	{
		Box* box = scene->GetGameObject<Box>();

		if (box)
		{
			Vector3 position3 = box->GetPosition();
			Vector3 scale = box->GetScale();

			// ボックスのAABB作成
			AABB aabbGoal;
			Vector3 GoalSize(2.0f, 2.0f, 2.0f);
			aabbGoal = SetAABB(
				position3,
				fabs(GoalSize.x * scale.x),
				fabs(GoalSize.y * scale.y),
				fabs(GoalSize.z * scale.z));

			// プレイヤのAABB作成
			AABB aabbPlayer;
			Vector3 PlayerSize(1.0f, 1.0f, 1.0f);
			aabbPlayer = SetAABB(
				Vector3(m_Position.x, m_Position.y + 1.0f, m_Position.z),
				fabs(PlayerSize.x * m_Scale.x),
				fabs(PlayerSize.y * m_Scale.y),
				fabs(PlayerSize.z * m_Scale.z));

			// AABB当たり判定
			bool sts = CollisionAABB(aabbPlayer, aabbGoal);

			if (sts)
			{
				GameObject* child = AddChild<Box>();
				Vector3 scale = child->GetScale();
				scale = box->GetScale();
				scale *= 0.1f;
				//scale *= this->m_Scale;
				child->SetScale(scale);

				//一番近い頂点座標を取ってくる
				Vector3 pos = GetClosestVeretex(m_VertexPos, box->GetPosition());
				
				Vector3 fPos;
				fPos.x	= fabs(m_Position.x);
				fPos.y = fabs(m_Position.y);
				fPos.z = fabs(m_Position.z);

				Vector3 fPosBox;
				fPosBox.x = fabs(box->GetPosition().x);
				fPosBox.y = fabs(box->GetPosition().y);
				fPosBox.z = fabs(box->GetPosition().z);
				
				//pos = pos * fPos - (fPosBox - box->GetScale() - Vector3(0.5f, 0.5f, 0.5f));

				//Camera* camera = scene->GetGameObject<Camera>();							

				child->SetPosition(pos);

				m_Children.push_back(child);
				mchild = child;
				box->SetDestroy();
			}
		}
	}	

	//弾発射
	if (Input::GetKeyTrigger('K'))
	{
		Scene* scene = Manager::GetScene();
		Bullet* bullet = scene->AddGameObject<Bullet>(2);
		bullet->SetPosition(m_Position + Vector3(0.0f, 1.0f, 0.0f));
		bullet->SetVelocity(this->GetForward() * 0.5f);

		m_SE->Play();
	}
}

void Player::Draw()
{
	for (auto& cmpt : m_Component) {
		cmpt->Draw();
	}		

	//プレイヤーの情報を表示する
	ImGui::Begin("Player");
	ImGui::Text("PlayerScale\n %f\nY %f\nZ %f",this->m_Scale.x,this->m_Scale.y,this->m_Scale.z);
	ImGui::Text("PlayerPos\nX %f\nY %f\nZ %f", this->m_Position.x, this->m_Position.y, this->m_Position.z);
	ImGui::Text("PlayerRot\nX %f\nY %f\nZ %f", this->m_Rotation.x, this->m_Rotation.y, this->m_Rotation.z);
	ImGui::Text("PlayerFow\nX %f\nY %f\nZ %f", this->GetForward().x, this->GetForward().y, this->GetForward().z);
	ImGui::End();	

	if (mchild != nullptr)
	{
		ImGui::Begin("Child");
		ImGui::Text("Scale\n %f\nY %f\nZ %f", mchild->GetScale().x, mchild->GetScale().y, mchild->GetScale().z);
		ImGui::Text("Pos\nX %f\nY %f\nZ %f", mchild->GetPosition().x, mchild->GetPosition().y, mchild->GetPosition().z);
		ImGui::Text("Rot\nX %f\nY %f\nZ %f", mchild->GetRotation().x, mchild->GetRotation().y, mchild->GetRotation().z);
		ImGui::End();
	}
}