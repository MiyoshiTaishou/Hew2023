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

//�`��
#include"../Render/modelRenderer.h"

//ImGui
#include"../ImGui/ImGuiManager.h"

//�I�u�W�F�N�g
#include"../Object/BoxObject.h"

using namespace DirectX::SimpleMath;

void Player::Init()
{
	//���W�A�T�C�Y�ݒ�
	this->m_Scale = Vector3(10.0f, 10.0f, 10.f);
	this->m_Position.x = 10.0f;
	this->m_Position.z = 0.0f;

	//�R���|�[�l���g
	//AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\vertexLightingPS.cso");
	//AddComponent<Shader>()->Load("../shader\\VS_GouraudShading.cso", "../shader\\PS_OrangeScale.cso");
	AddComponent<Shader>()->Load("../shader\\VS_Object.cso", "../shader\\PS_Toon.cso");
	ModelRenderer* model = AddComponent<ModelRenderer>();
	//model->Load("../asset\\model\\bullet.obj");
	model->Load("../asset\\model\\bullet.obj");

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
	//�R���g���[���[����
	ConInput();

	//�����蔻�菈��
	Collision();

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
	ImGui::End();
}

void Player::Collision()
{
	// ���݃V�[�����擾
	Scene* scene = Manager::GetScene();

	//�{�b�N�X�Ƃ̓����蔻��
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

//���͏���
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
