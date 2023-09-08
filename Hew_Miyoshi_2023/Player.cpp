#include<SimpleMath.h>
#include "Player.h"
#include"modelRenderer.h"
#include"shader.h"
#include"JumpComponent.h"
#include"BoxCollider.h"
#include"audio.h"
#include"scene.h"
#include"manager.h"
#include"Goal.h"
#include"collison.h"
#include"input.h"
#include"box.h"
#include"Enemy.h"
#include"camera.h"
#include"AddForce.h"
#include"OBBCollison.h"
#include"StageHit.h"
#include"score.h"
#include"Trampoline.h"
#include"DragFloor.h"

#include"ImGuiManager.h"

using namespace DirectX::SimpleMath;

void Player::Init()
{
	//AddComponent<Shader>()->Load("shader\\VS_GouraudShading.cso", "shader\\PS_GouraudShading.cso");	
	//AddComponent<Shader>()->Load("shader\\VS_GouraudShading.cso", "shader\\PS_BloomBlur.cso");
	AddComponent<Shader>()->Load("shader\\VS_GouraudShading.cso", "shader\\PS_OrangeScale.cso");
	//AddComponent<Shader>()->Load("shader\\VS_GouraudShading.cso", "shader\\PS_PolarCoordinates.cso");	
	AddComponent<Rigidbody>()->Init(2, -1, 1);
	//AddComponent<ModelRenderer>()->Load("asset\\model\\bullet.obj");
	m_VertexPos = AddComponent<ModelRenderer>()->LoadVertex("asset\\model\\bullet.obj");
	//AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso", "shader\\PS_RGBSplit.cso");	

	this->m_Scale = Vector3(10.0f, 10.0f, 10.f);
	//this->m_Position.y = 10.0f;
	this->m_Position.x = 10.0f;
	this->m_Position.z = -10.0f;

	m_SE = AddComponent<Audio>();
	m_SE->Load("asset\\audio\\wan.wav");

	m_MeatSE = AddComponent<Audio>();
	m_MeatSE->Load("asset\\audio\\�Ղ��_2.wav");

	m_MeatSE2 = AddComponent<Audio>();
	m_MeatSE2->Load("asset\\audio\\�{����.wav");
}

void Player::Update()
{
	// ���݃V�[�����擾
	Scene* scene = Manager::GetScene();

	Camera* cameraObj = scene->GetGameObject<Camera>();

	Vector3 oldPosition = m_Position;

	Rigidbody* body = GetComponent<Rigidbody>();
	
	//�ڒn
	float groundHeight = 2.0f;

	Vector3 forward = Vector3(0, 0, 0);

	//�J�����̑O�����x�N�g��
	if(cameraObj)
		forward = cameraObj->GetForward();	

	//�d��
	m_Velocity.y -= 0.015f;

	//��R
	m_Velocity.y -= m_Velocity.y * 0.01f;

	//�R���g���[���[�̓��͂����	
	{
		if (wallUp)
		{
			if (Input::GetGamePad(BUTTON::LUP, STATE::HELD) && Input::GetGamePad(BUTTON::RUP, STATE::HELD))
			{
				Vector3 Up = Vector3(0.0f, 1000.0f, 0.0f);				
				body->AddForce(Up, ForceMode::Force);
			}
		}
		else
		{
			if (Input::GetGamePad(BUTTON::LUP, STATE::HELD) && Input::GetGamePad(BUTTON::RUP, STATE::HELD))
			{
				Vector3 force = forward * 100.0f;
				body->AddForce(force, ForceMode::Force);
				m_Rotation.x += 0.1f;
			}
			if (Input::GetGamePad(BUTTON::LDOWN, STATE::HELD) && Input::GetGamePad(BUTTON::RDOWN, STATE::HELD))
			{
				Vector3 force = forward * -100.0f;
				body->AddForce(force, ForceMode::Force);
				m_Rotation.x -= 0.1f;
			}
			if (Input::GetGamePad(BUTTON::LLEFT, STATE::HELD))
				m_Rotation.y -= 1.0f / 60.0f;
			if (Input::GetGamePad(BUTTON::LRIGHT, STATE::HELD))
				m_Rotation.y += 1.0f / 60.0f;


			//�_�b�V��
			if (Input::GetGamePad(BUTTON::LUP, STATE::PRESSED) && Input::GetGamePad(BUTTON::RDOWN, STATE::PRESSED))
			{
				actionCheck = true;
				actionCount++;
			}
			if (Input::GetGamePad(BUTTON::LDOWN, STATE::PRESSED) && Input::GetGamePad(BUTTON::RUP, STATE::PRESSED))
			{
				actionCheck = true;
				actionCount++;
			}
		}		
	}

	// �S�[���Ƃ̓����蔻��
	{
		Goal* goal = scene->GetGameObject<Goal>();
		//std::vector<Goal*> goal = scene->GetGameObjects<Goal>();

		if (goal)
		{
			Vector3 position = goal->GetPosition();
			Vector3 scale = goal->GetScale();
			Vector3 rotate = goal->GetRotation();

			//�S�[����OBB�ݒ�
			OBBinfo goalOBB;
			goalOBB.center = Vector3(0.0f, 0.0f, 0.0f);
			goalOBB.currentcenter = position;
			goalOBB.fLengthX = scale.x * 2 / 2;
			goalOBB.fLengthY = scale.y * 2 / 2;
			goalOBB.fLengthZ = scale.z * 2 / 2;
			goalOBB.vecAxisX = Vector3(cosf(rotate.y) * cosf(rotate.z),
				sinf(rotate.z),
				sinf(rotate.y) * cosf(rotate.z));
			goalOBB.vecAxisY = Vector3(-cosf(rotate.y) * sinf(rotate.z),
				cosf(rotate.z),
				-sinf(rotate.y) * sinf(rotate.z));
			goalOBB.vecAxisZ = Vector3(-sinf(rotate.y),
				0.0f,
				cosf(rotate.y));

			OBBinfo pOBB;
			pOBB.center = Vector3(0.0f, 0.0f, 0.0f);
			pOBB.currentcenter = m_Position;
			pOBB.fLengthX = m_Scale.x * 3 / 2;
			pOBB.fLengthY = m_Scale.y * 2 / 2;
			pOBB.fLengthZ = m_Scale.z / 2;

			Matrix rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);

			pOBB.vecAxisX = rot._31 * Vector3(1.0f, 0.0f, 0.0f);
			pOBB.vecAxisY = rot._32 * Vector3(0.0f, 1.0f, 0.0f);
			pOBB.vecAxisZ = rot._33 * Vector3(0.0f, 0.0f, 1.0f);

			////���������߂�
			//Vector3 direction = m_Position - position;
			//float length = direction.Length();
			//float radius = fabs(m_Scale.x / 2.0f);

			//if (length < radius)
			//	goal->SetDestroy();

			bool sts = Collisom(pOBB, goalOBB);

			if (sts)
				goal->SetDestroy();
		}

	}

	//�G�l�~�[�̓����蔻��
	{
		std::vector<Enemy*> enemylist = scene->GetGameObjects<Enemy>();

		for (auto& enemyObj : enemylist)
		{
			Vector3 position = enemyObj->GetPosition();
			Vector3 scale = enemyObj->GetScale();
			
			//���������߂�
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

				//��ԋ߂����_���W������Ă���
				Vector3 pos = GetClosestVeretex(m_VertexPos, enemyObj->GetPosition());
				pos *= this->GetForward() * 1.8f;

				child->SetPosition(pos);

				m_Children.push_back(child);
				mchild = child;
				enemyObj->SetDestroy();

				m_MeatSE->Play();

				/*Score* score = scene->GetGameObject<Score>();
				score->AddCount(1);*/
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

			//�v���C���[��BS�쐬
			BoundingSphere playerBS{};
			playerBS.center = m_Position;
			playerBS.radius = fabs(m_Scale.x / 2.0f);

			//bool sts CollisionSphereOrientedQuad(position)

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

			if (position.x - scale.x - 1.0f < m_Position.x && m_Position.x < position.x + scale.x + 1.0f &&
				position.z - scale.z - 1.0f < m_Position.z && m_Position.z < position.z + scale.z + 1.0f)
			{
				if (m_Position.y < position.y + scale.y * 2.0f - 0.5f)
				{
					Vector3 vel = body->GetVelocity();

					//������ւ̑��x�͖�������
					vel.y = 0.0f;
					float speed = vel.Length();

					//��葬�x�ȉ��Ȃ�Ǔo��ɂȂ�
					if (speed > 10.0f)
					{
						Vector3 force = -vel * 5.0f;
						body->AddForce(force, ForceMode::Impulse);

						m_MeatSE2->Play();
					}
					else
					{
						m_Position.x = oldPosition.x;
						m_Position.z = oldPosition.z;
						Vector3 v = body->GetVelocity();
						body->SetVelocity({ 0.0f,v.y,0.0f });
						//body->SetForce(Vector3(0.0f, 0.0f, 0.0f));
						//�Ǔo��ł���
						wallUp = true;
					}
				}
				else
				{
					groundHeight = position.y + scale.y * 2.0f + 2.0f;
					wallUp = false;
				}					
			}
		}
	}

	//�g�����|����
	{
		Trampoline* trampoline = scene->GetGameObject<Trampoline>();

		if (trampoline)
		{
			Vector3 position = trampoline->GetPosition();
			Vector3 scale = trampoline->GetScale();

			//�v���C���[��BS�쐬
			BoundingSphere playerBS{};
			playerBS.center = m_Position;
			playerBS.radius = fabs(m_Scale.x / 2.0f);

			//bool sts CollisionSphereOrientedQuad(position)

			//�������
			Vector3 PWidth = m_Position - m_Scale - Vector3(0.5f, 0.5f, 0.5f);
			Vector3 BWidth = position - scale - Vector3(0.5f, 0.5f, 0.5f);

			if (position.x - scale.x - 0.5f < m_Position.x && m_Position.x < position.x + scale.x + 0.5f &&
				position.z - scale.z - 0.5f < m_Position.z && m_Position.z < position.z + scale.z + 0.5f &&
				PWidth.x > BWidth.x && PWidth.y > BWidth.y && PWidth.z > BWidth.z)
			{
				GameObject* child = AddChild<Box>();
				Vector3 scale = child->GetScale();
				scale = trampoline->GetScale();
				scale *= 0.1f;
				child->SetScale(scale);

				//��ԋ߂����_���W������Ă���
				Vector3 pos = GetClosestVeretex(m_VertexPos, trampoline->GetPosition());
				pos *= this->GetForward();

				child->SetPosition(pos);

				m_Children.push_back(child);
				mchild = child;
				trampoline->SetDestroy();
			}

			if (position.x - scale.x - 0.5f < m_Position.x && m_Position.x < position.x + scale.x + 0.5f &&
				position.z - scale.z - 0.5f < m_Position.z && m_Position.z < position.z + scale.z + 0.5f)
			{
				if (m_Position.y < position.y + scale.y * 2.0f - 0.5f)
				{
					Vector3 vel = body->GetVelocity();
					float absVelX = fabs(vel.x);
					float absVelZ = fabs(vel.z);

					if (absVelX > 4.0f || absVelX > 4.0f)
					{
						Vector3 force = -vel * 5.0f;
						//GetComponent<Rigidbody>()->AddForce(force, ForceMode::Impuluse);

						m_MeatSE2->Play();
					}
					else
					{
						body->SetFreeze(Freeze::Xpos, true);
						body->SetFreeze(Freeze::ZPos, true);
					}
				}
				else if (position.y + scale.y * 2.0f + 1.0f < m_Position.y && position.y + scale.y * 2.0f + 3.0f > m_Position.y)
				{
					groundHeight = position.y + scale.y * 2.0f + 2.0f;
					trampoline->Action(this);
				}
			}
		}
	}

	//���C��
	{
		DragFloor* floor = scene->GetGameObject<DragFloor>();

		if (floor)
		{
			Vector3 position = floor->GetPosition();
			Vector3 scale = floor->GetScale();

			//�v���C���[��BS�쐬
			BoundingSphere playerBS{};
			playerBS.center = m_Position;
			playerBS.radius = fabs(m_Scale.x / 2.0f);

			//bool sts CollisionSphereOrientedQuad(position)

			//�������
			Vector3 PWidth = m_Position - m_Scale - Vector3(0.5f, 0.5f, 0.5f);
			Vector3 BWidth = position - scale - Vector3(0.5f, 0.5f, 0.5f);

			if (position.x - scale.x - 0.5f < m_Position.x && m_Position.x < position.x + scale.x + 0.5f &&
				position.z - scale.z - 0.5f < m_Position.z && m_Position.z < position.z + scale.z + 0.5f &&
				PWidth.x > BWidth.x && PWidth.y > BWidth.y && PWidth.z > BWidth.z)
			{
				GameObject* child = AddChild<Box>();
				Vector3 scale = child->GetScale();
				scale = floor->GetScale();
				scale *= 0.1f;
				child->SetScale(scale);

				//��ԋ߂����_���W������Ă���
				Vector3 pos = GetClosestVeretex(m_VertexPos, floor->GetPosition());
				pos *= this->GetForward();

				child->SetPosition(pos);

				m_Children.push_back(child);
				mchild = child;
				floor->SetDestroy();
			}

			if (position.x - scale.x - 0.5f < m_Position.x && m_Position.x < position.x + scale.x + 0.5f &&
				position.z - scale.z - 0.5f < m_Position.z && m_Position.z < position.z + scale.z + 0.5f)
			{
				if (m_Position.y < position.y + scale.y * 2.0f - 0.5f)
				{
					Vector3 vel = body->GetVelocity();
					float absVelX = fabs(vel.x);
					float absVelZ = fabs(vel.z);

					if (absVelX > 4.0f || absVelX > 4.0f)
					{
						Vector3 force = -vel * 5.0f;
						//GetComponent<Rigidbody>()->AddForce(force, ForceMode::Impuluse);

						m_MeatSE2->Play();
					}
					else
					{
						body->SetFreeze(Freeze::Xpos, true);
						body->SetFreeze(Freeze::ZPos, true);
					}
				}
				else if (position.y + scale.y * 2.0f + 1.0f < m_Position.y && position.y + scale.y * 2.0f + 3.0f > m_Position.y)
				{
					groundHeight = position.y + scale.y * 2.0f + 2.0f;	
					body->SetDrag(1);
				}
			}
			else
			{
				body->InitDrag();
			}
		}
	}

	// �ʒu���O�ȉ��Ȃ�n�ʈʒu�ɃZ�b�g����
	if (m_Position.y < groundHeight)
	{
		Vector3 vel = body->GetVelocity();
		m_Position.y = groundHeight;
		vel.y = 0.0f;
		body->SetVelocity(vel);
	}
	
	//���݂̈ʒu���X�V	
	if (Input::GetKeyPress('A'))
	{
		m_Rotation.y -= buttonState.thumbSticks.leftX / 60.0f;
		m_Rotation.y -= 1.0f / 60.0f;
	}

	if (Input::GetKeyPress('D'))
	{
		m_Rotation.y += 1.0f / 60.0f;
	}	

	if (Input::GetKeyPress('W') || this->buttonState.IsLeftStickPressed())
	{
		if (body->GetFreeze(Freeze::Xpos))
		{
			Vector3 force = { 0,500,0 };
			body->AddForce(force, ForceMode::Force);
		}
		else
		{
			Vector3 force = forward * 100.0f;
			body->AddForce(force, ForceMode::Force);
		}
	}

	if (Input::GetKeyPress('S'))
	{
		Vector3 force = forward * -100.0f;
		body->AddForce(force, ForceMode::Force);
	}

	//�W�����v
	if (Input::GetKeyTrigger('J'))
	{
		Vector3 force = { 0,100,0 };
		body->AddForce(force, ForceMode::Impulse);
	}


	//�n�ʂƂ̓����蔻��
	Vector3 ans;
	bool sts = SearchAllSurface(m_Position.x, m_Position.z, ans);
	if (sts) {
		m_Position.y = ans.y;
	}
	else {
		m_Position.y = m_Position.y;
	}

	//��t����true�Ȃ�v���J�n
	if (actionCheck)
	{
		if (loopCount < reception)
			if (actionDashu < actionCount)
			{
				Vector3 force = forward * 100.0f;
				body->AddForce(force, ForceMode::Impulse);
				actionCheck = false;
				actionDashu = 0;
				loopCount = 0;
			}

		loopCount++;
	}
	else
	{
		loopCount = 0;
		actionDashu = 0;
	}

	for (auto& cmpt : m_Component) {
		cmpt->Update();
	}

	//���W�X�V
	m_Position += body->GetVelocity() * (1.0f / 60.0f);	
}

void Player::Draw()
{
	for (auto& cmpt : m_Component) {
		cmpt->Draw();
	}

	//�v���C���[�̏���\������
	ImGui::Begin("Player");
	ImGui::Text("PlayerScale\n %f\nY %f\nZ %f", this->m_Scale.x, this->m_Scale.y, this->m_Scale.z);
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