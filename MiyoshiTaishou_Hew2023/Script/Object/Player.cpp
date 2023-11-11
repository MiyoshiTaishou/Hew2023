#include<SimpleMath.h>

#include "Player.h"

//�Ǘ�
#include"../Sysytem/manager.h"

//�V�[��
#include"../Scene/scene.h"

//����
#include"../Sysytem/input.h"

//�R���|�[�l���g
#include"../Component/shader.h"
#include"../Component/BoxCollider.h"
#include"../Component/RigidBody.h"
#include"../Component/shadow.h"

//�`��
#include"../Render/modelRenderer.h"

//ImGui
#include"../ImGui/ImGuiManager.h"

//�I�u�W�F�N�g
#include"BoxObject.h"
#include"camera.h"
#include"field.h"

//UI
#include"../UI/score.h"

using namespace DirectX::SimpleMath;

void Player::Init()
{
	//���W�A�T�C�Y�ݒ�
	this->m_Scale = Vector3(10.0f, 10.0f, 10.f);
	this->m_Position.x = 10.0f;
	this->m_Position.z = 0.0f;

	//�R���|�[�l���g
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

	//�����蔻��̑傫�����I�u�W�F�N�g�ɍ��킹��
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
	//�����蔻�菈��
	Collision();

	//�R���g���[���[����
	ConInput();

	//�R���|�[�l���g��Update�Ăяo��
	for (auto& cmpt : m_Component) {
		cmpt->Update();
	}
}

void Player::Draw()
{
	//�v���C���[�̏���\������
	ImGui::Begin("Player");
	ImGui::Text("PlayerScale\n %f\nY %f\nZ %f", this->m_Scale.x, this->m_Scale.y, this->m_Scale.z);
	ImGui::Text("PlayerPos\nX %f\nY %f\nZ %f", this->m_Position.x, this->m_Position.y, this->m_Position.z);
	ImGui::Text("PlayerRot\nX %f\nY %f\nZ %f", this->m_Rotation.x, this->m_Rotation.y, this->m_Rotation.z);
	ImGui::Text("PlayerFow\nX %f\nY %f\nZ %f", this->GetForward().x, this->GetForward().y, this->GetForward().z);
	ImGui::Text("PlayerState\n %d", this->state);
	//�ړ����x
	ImGui::SliderFloat("Speed##", &m_Speed, 0.0f, 300.0f);
	ImGui::SliderFloat("SpeedRot##", &m_RotSpeed, 0.0f, 300.0f);
	ImGui::End();
}

void Player::Collision()
{
	// ���݃V�[�����擾
	Scene* scene = Manager::GetScene();	

	//�������I�u�W�F�N�g�����蔻��
	{
		std::vector<BoxObject*> boxlist = scene->GetGameObjects<BoxObject>();

		for (const auto& boxobj : boxlist)
		{			
			if (this->GetComponent<BoxCollider>()->Hit(boxobj->GetComponent<BoxCollider>()))
			{
				//����������
				StickObject* child = AddChild<BoxObject>();				
				child->Stick();						

				//�I�u�W�F�N�g�폜
				boxobj->SetDestroy();

				//�X�R�A���Z
				Score* score = scene->GetGameObject<Score>();
				score->AddCount(1);

				state = HIT;
			}
			else
			{
				state = IDLE;
			}
		}
	}
	
	//�������擾	
	float Height = scene->GetGameObject<Field>()->GetFieldHeight(m_Position);
	
	if (Height != 0.0f)
	{
		//pos.y = Height;
		m_Position.y = Height + 2;
	}		
}

//���͏���
void Player::ConInput()
{
	// ���݃V�[�����擾
	Scene* scene = Manager::GetScene();

	Camera* cameraObj = scene->GetGameObject<Camera>();

	RigidBody* body = GetComponent<RigidBody>();

	//�J�����̑O�����x�N�g��
	Vector3 forward = Vector3(0, 0, 0);	
	if (cameraObj)
	{
		forward = cameraObj->GetForward();
	}

	if (Input::GetGamePad(BUTTON::LUP)  && Input::GetGamePad(BUTTON::RUP))
	{
		Vector3 force = forward * m_Speed;
		Vector3 forceRot = forward * m_RotSpeed;

		body->AddForce(force, ForceMode::Force);
		body->AddTorque(forceRot, ForceMode::Force,false);
	}
	if (Input::GetGamePad(BUTTON::LDOWN) && Input::GetGamePad(BUTTON::RDOWN))
	{
		Vector3 force = forward * -m_Speed;
		Vector3 forceRot = forward * -m_RotSpeed;
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

	if (Input::GetGamePad(BUTTON::RDOWN) && Input::GetGamePad(BUTTON::LUP))
	{
		m_Rotation.y += 0.05f;
	}
	if (Input::GetGamePad(BUTTON::RUP) && Input::GetGamePad(BUTTON::LDOWN))
	{
		m_Rotation.y -= 0.05f;
	}

	if (Input::GetKeyTrigger('J'))
	{
		Vector3 force = { 0,100,0 };
		body->AddForce(force, ForceMode::Impulse);
	}
}
