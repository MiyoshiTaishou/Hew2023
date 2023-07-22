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
#include"Enemy.h"
#include"camera.h"
#include"AddForce.h"

#include"ImGuiManager.h"

using namespace DirectX::SimpleMath;

void Player::Init()
{			
	//AddComponent<Shader>()->Load("shader\\VS_GouraudShading.cso", "shader\\PS_GouraudShading.cso");	
	AddComponent<Rigidbody>()->Init(2,-1,1);
	//AddComponent<ModelRenderer>()->Load("asset\\model\\bullet.obj");
	m_VertexPos =  AddComponent<ModelRenderer>()->LoadVertex("asset\\model\\bullet.obj");	
	AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso", "shader\\PS_RGBSplit.cso");
	//AddComponent<PhysicsComponent>()->Init();		
	//AddComponent<JumpComponent>()->Init();				

	this->m_Scale = Vector3(10.0f, 10.0f, 10.f);
	//this->m_Position.y = 10.0f;
	this->m_Position.x = 10.0f;		
	this->m_Position.z = -10.0f;		

	m_SE = AddComponent<Audio>();
	m_SE->Load("asset\\audio\\wan.wav");

	//m_Size=
}

void Player::Uninit()
{
	
}


void Player::Update()
{	
	// 現在シーンを取得
	Scene* scene = Manager::GetScene();

	Camera* cameraObj = scene->GetGameObject<Camera>();

	Vector3 oldPosition = m_Position;

	GetComponent<Rigidbody>()->SetFreeze(Freeze::Xpos, false);
	GetComponent<Rigidbody>()->SetFreeze(Freeze::ZPos, false);

	//接地
	float groundHeight = 2.0f;

	//カメラの前向きベクトル
	Vector3 forward = cameraObj->GetForward();

	for (auto& cmpt : m_Component) {
		cmpt->Update();
	}	
	
	
	//重力
	m_Velocity.y -= 0.015f;

	//抵抗
	m_Velocity.y -= m_Velocity.y * 0.01f;	

	// ゴールとの当たり判定
	{
		Goal* goal = scene->GetGameObject<Goal>();
		//std::vector<Goal*> goal = scene->GetGameObjects<Goal>();

		if (goal)
		{
			Vector3 position = goal->GetPosition();
			Vector3 scale = goal->GetScale();

			//距離を求める
			Vector3 direction = m_Position - position;
			float length = direction.Length();
			float radius = fabs(m_Scale.x / 2.0f);

			if (length < radius)
				goal->SetDestroy();
		}

	}

	//エネミーの当たり判定
	{
		std::vector<Enemy*> enemylist = scene->GetGameObjects<Enemy>();

		for (auto& enemyObj : enemylist)
		{
			Vector3 position = enemyObj->GetPosition();
			Vector3 scale = enemyObj->GetScale();

			//// エネミーのAABB作成
			//AABB aabbEnemy;
			//Vector3 EnemySize(1.0f, 1.0f, 1.0f);
			//aabbEnemy = SetAABB(
			//	position,
			//	fabs(EnemySize.x * scale.x),
			//	fabs(EnemySize.y * scale.y),
			//	fabs(EnemySize.z * scale.z));

			//// プレイヤのAABB作成
			//AABB aabbPlayer;
			//Vector3 PlayerSize(1.0f, 1.0f, 1.0f);
			//aabbPlayer = SetAABB(
			//	Vector3(m_Position.x, m_Position.y + 1.0f, m_Position.z),
			//	fabs(PlayerSize.x * m_Scale.x),
			//	fabs(PlayerSize.y * m_Scale.y),
			//	fabs(PlayerSize.z * m_Scale.z));			

			//距離を求める
			Vector3 direction = m_Position - position;
			float length = direction.Length();
			float radius = fabs(m_Scale.x / 2.0f);

			bool sts = false;

			if (length < radius)
				sts = true;
			
			if (sts)
			{
				GameObject* child = AddChild<Enemy>();
				Vector3 scale = child->GetScale();
				scale = enemyObj->GetScale();
				scale *= 0.1f;
				child->SetScale(scale);

				//一番近い頂点座標を取ってくる
				Vector3 pos = GetClosestVeretex(m_VertexPos, enemyObj->GetPosition());
				pos *= this->GetForward() * 1.8f;

				child->SetPosition(pos);

				m_Children.push_back(child);
				mchild = child;
				enemyObj->SetDestroy();
			}
		}
	}

	//Boxの当たり判定
	{
		std::vector<Box*> boxlist = scene->GetGameObjects<Box>();

		for (const auto& boxobj : boxlist)
		{
			Vector3 position = boxobj->GetPosition();
			Vector3 scale = boxobj->GetScale();

			//プレイヤーのBS作成
			BoundingSphere playerBS{};
			playerBS.center = m_Position;
			playerBS.radius = fabs(m_Scale.x / 2.0f);

			//bool sts CollisionSphereOrientedQuad(position)

			//幅を取る
			Vector3 PWidth = m_Position - m_Scale - Vector3(0.5f, 0.5f, 0.5f);
			Vector3 BWidth = position - scale - Vector3(0.5f, 0.5f, 0.5f);

			if (position.x - scale.x - 0.5f < m_Position.x && m_Position.x < position.x + scale.x + 0.5f &&
				position.z - scale.z - 0.5f < m_Position.z && m_Position.z < position.z + scale.z + 0.5f &&
				PWidth.x > BWidth.x && PWidth.y > BWidth.y && PWidth.z > BWidth.z)
			{
				GameObject* child = AddChild<Box>();
				Vector3 scale = child->GetScale();
				scale = boxobj->GetScale();
				scale *= 0.1f;				
				child->SetScale(scale);

				//一番近い頂点座標を取ってくる
				Vector3 pos = GetClosestVeretex(m_VertexPos, boxobj->GetPosition());
				pos *= this->GetForward();

				child->SetPosition(pos);

				m_Children.push_back(child);
				mchild = child;
				boxobj->SetDestroy();
			}

			if (position.x - scale.x - 0.5f < m_Position.x && m_Position.x < position.x + scale.x + 0.5f &&
				position.z - scale.z - 0.5f < m_Position.z && m_Position.z < position.z + scale.z + 0.5f)
			{
				if (m_Position.y < position.y + scale.y * 2.0f - 0.5f)
				{
					Vector3 vel = GetComponent<Rigidbody>()->GetVelocity();
					float absVelX = fabs(vel.x);
					float absVelZ = fabs(vel.z);

					if (absVelX > 4.0f || absVelX > 4.0f)
					{
						Vector3 force = -vel * 5.0f;
						GetComponent<Rigidbody>()->AddForce(force, ForceMode::Impuluse);
					}
					else
					{
						GetComponent<Rigidbody>()->SetFreeze(Freeze::Xpos,true);
						GetComponent<Rigidbody>()->SetFreeze(Freeze::ZPos,true);
					}
				}			
				else
					groundHeight = position.y + scale.y * 2.0f + 2.0f;
			}							
		}
	}	

	// 位置が０以下なら地面位置にセットする
	if (m_Position.y < groundHeight)
	{
		Vector3 vel = GetComponent<Rigidbody>()->GetVelocity();
		m_Position.y = groundHeight;	
		vel.y = 0.0f;
		GetComponent<Rigidbody>()->SetVelocity(vel);
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

	//現在の位置を更新	
	if (Input::GetKeyPress('A'))
	{
		m_Rotation.y -= 1.0f / 60.0f;
	}
	if (Input::GetKeyPress('D'))
	{
		m_Rotation.y += 1.0f / 60.0f;
	}

	if (Input::GetKeyPress('W'))
	{
		if (GetComponent<Rigidbody>()->GetFreeze(Freeze::Xpos))
		{
			Vector3 force = { 0,500,0 };
			GetComponent<Rigidbody>()->AddForce(force, ForceMode::Force);
		}
		else
		{
			Vector3 force = forward * 100.0f;
			GetComponent<Rigidbody>()->AddForce(force, ForceMode::Force);
		}
	}

	if (Input::GetKeyPress('S'))
	{				
		Vector3 force = forward * -100.0f;
		GetComponent<Rigidbody>()->AddForce(force, ForceMode::Force);
	}

	//ジャンプ
	if (Input::GetKeyTrigger('J'))
	{
		Vector3 force = { 0,100,0 };
		GetComponent<Rigidbody>()->AddForce(force, ForceMode::Impuluse);
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