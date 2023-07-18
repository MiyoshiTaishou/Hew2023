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

#include"ImGuiManager.h"

using namespace DirectX::SimpleMath;

void Player::Init()
{			
	AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");
	//AddComponent<ModelRenderer>()->Load("asset\\model\\bullet.obj");
	m_VertexPos =  AddComponent<ModelRenderer>()->LoadVertex("asset\\model\\bullet.obj");	
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
	// ���݃V�[�����擾
	Scene* scene = Manager::GetScene();

	Camera* cameraObj = scene->GetGameObject<Camera>();

	Vector3 oldPosition = m_Position;

	//�ڒn
	float groundHeight = 2.0f;

	for (auto& cmpt : m_Component) {
		cmpt->Update();
	}	

	//�������x�^��
	float m = (velocity * time) + ((acc * (time * time)) / 2);

	//�����̏��
	if (m > 0.5f)
		m = 0.5f;

	vel = m;

	Vector3 Vecm = Vector3(m, m, m);

	//���݂̈ʒu���X�V	
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
		m_Rotation.x += 5.0f / 60.f;
		m_Position += (cameraObj->GetForward() * Vecm);
		time += 0.1;
	}

	if (Input::GetKeyPress('S'))
	{
		m_Rotation.x -= 5.0f / 60.f;
		m_Position -= (cameraObj->GetForward() * Vecm);
		time += 0.1;
	}

	//�W�����v
	if (Input::GetKeyTrigger('J'))
	{
		m_Velocity.y = 0.35f;
	}

	//�d��
	m_Velocity.y -= 0.015f;

	//��R
	m_Velocity.y -= m_Velocity.y * 0.01f;

	//�ړ�
	m_Position += m_Velocity;

	time -= 0.05;

	if (time < 0)
		time = 0;

	// �S�[���Ƃ̓����蔻��
	{
		Goal* goal = scene->GetGameObject<Goal>();
		//std::vector<Goal*> goal = scene->GetGameObjects<Goal>();

		if (goal)
		{
			Vector3 position = goal->GetPosition();
			Vector3 scale = goal->GetScale();

			// �S�[����AABB�쐬
			AABB aabbGoal;
			Vector3 GoalSize(2.0f, 2.0f, 2.0f);
			aabbGoal = SetAABB(
				position,
				fabs(GoalSize.x * scale.x),
				fabs(GoalSize.y * scale.y),
				fabs(GoalSize.z * scale.z));

			// �v���C����AABB�쐬
			AABB aabbPlayer;
			Vector3 PlayerSize(1.0f, 2.0f, 1.0f);
			aabbPlayer = SetAABB(
				Vector3(m_Position.x, m_Position.y + 1.0f, m_Position.z),
				fabs(PlayerSize.x * m_Scale.x),
				fabs(PlayerSize.y * m_Scale.y),
				fabs(PlayerSize.z * m_Scale.z));

			//BoundingSphere playerBS{};

			// AABB�����蔻��
			bool sts = CollisionAABB(aabbPlayer, aabbGoal);

			if (sts)
			{
				goal->SetDestroy();
			}
		}

	}

	//�G�l�~�[�̓����蔻��
	{
		std::vector<Enemy*> enemylist = scene->GetGameObjects<Enemy>();

		for (auto& enemyObj : enemylist)
		{
			Vector3 position = enemyObj->GetPosition();
			Vector3 scale = enemyObj->GetScale();

			// �G�l�~�[��AABB�쐬
			AABB aabbEnemy;
			Vector3 EnemySize(1.0f, 1.0f, 1.0f);
			aabbEnemy = SetAABB(
				position,
				fabs(EnemySize.x * scale.x),
				fabs(EnemySize.y * scale.y),
				fabs(EnemySize.z * scale.z));

			// �v���C����AABB�쐬
			AABB aabbPlayer;
			Vector3 PlayerSize(1.0f, 1.0f, 1.0f);
			aabbPlayer = SetAABB(
				Vector3(m_Position.x, m_Position.y + 1.0f, m_Position.z),
				fabs(PlayerSize.x * m_Scale.x),
				fabs(PlayerSize.y * m_Scale.y),
				fabs(PlayerSize.z * m_Scale.z));			

			// AABB�����蔻��
			bool sts = CollisionAABB(aabbPlayer, aabbEnemy);

			if (sts)
			{
				GameObject* child = AddChild<Enemy>();
				Vector3 scale = child->GetScale();
				scale = enemyObj->GetScale();
				scale *= 0.1f;
				child->SetScale(scale);

				//��ԋ߂����_���W������Ă���
				Vector3 pos = GetClosestVeretex(m_VertexPos, enemyObj->GetPosition());
				pos *= this->GetForward() * 1.8f;

				child->SetPosition(pos);

				m_Children.push_back(child);
				mchild = child;
				enemyObj->SetDestroy();
			}
		}
	}

	//Box�̓����蔻��
	{
		std::vector<Box*> boxlist = scene->GetGameObjects<Box>();

		for (const auto& boxobj : boxlist)
		{
			Vector3 position = boxobj->GetPosition();
			Vector3 scale = boxobj->GetScale();

			//�������
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

				//��ԋ߂����_���W������Ă���
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
					m_Position.x = oldPosition.x;
					m_Position.z = oldPosition.z;
				}			
				else
					groundHeight = position.y + scale.y * 2.0f + 2.0f;
			}							
		}
	}	

	// �ʒu���O�ȉ��Ȃ�n�ʈʒu�ɃZ�b�g����
	if (m_Position.y < groundHeight)
	{
		m_Position.y = groundHeight;	
		m_Velocity.y = 0.0f;
	}

	//�e����
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

	//�v���C���[�̏���\������
	ImGui::Begin("Player");
	ImGui::Text("PlayerScale\n %f\nY %f\nZ %f",this->m_Scale.x,this->m_Scale.y,this->m_Scale.z);
	ImGui::Text("PlayerPos\nX %f\nY %f\nZ %f", this->m_Position.x, this->m_Position.y, this->m_Position.z);
	ImGui::Text("PlayerRot\nX %f\nY %f\nZ %f", this->m_Rotation.x, this->m_Rotation.y, this->m_Rotation.z);
	ImGui::Text("PlayerFow\nX %f\nY %f\nZ %f", this->GetForward().x, this->GetForward().y, this->GetForward().z);	
	ImGui::Text("Time%f\n", time);
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