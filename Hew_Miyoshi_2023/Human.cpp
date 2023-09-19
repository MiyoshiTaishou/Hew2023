#include "Human.h"
#include "shader.h"
#include"shadow.h"
#include"ImGuiManager.h"

using namespace DirectX::SimpleMath;

void Human::Init()
{
	AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");

	//�A�j���[�V�������[�h����
	m_Model = AddComponent<AnimationModel>();

	m_Model->Load("asset\\model\\Capoeira.fbx");									// animation ok
	m_Model->LoadAnimation("asset\\model\\Rumba Dancing.fbx", "Idle");
	m_Model->LoadAnimation("asset\\model\\Capoeira.fbx", "Run");

	//�e
	AddComponent<Shadow>()->SetSize(1.5f);

	m_Scale = Vector3(0.02f, 0.02f, 0.02f);
}

void Human::Update()
{
	//���t���[���A�j���[�V�����X�V
	m_Frame++;
}

void Human::Draw()
{
	ImGui::Begin("AnimationModel");
	// �X���C�_�[
	ImGui::SliderFloat("Blend", &m_BlendRate, 0.0f, 1.0f);
	ImGui::End();
}

void Human::PreDraw()
{
	m_Model->Update("Idle", m_Frame, "Run", m_Frame, m_BlendRate);
}
