#include "Human.h"
#include "shader.h"
#include"shadow.h"
#include"dx11mathutil.h"
#include"ImGuiManager.h"

using namespace DirectX::SimpleMath;

void Human::Init()
{
	//AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");
	//AddComponent<Shader>()->Load("shader\\VS_LightingOneSkin.cso", "shader\\vertexLightingPS.cso"); //20230909-02

	// �g�p����V�F�[�_�[�𐶐�
	g_shader.SetShader("shader/vertexLightingVS.hlsl", "shader/vertexLightingPS.hlsl");
	//g_shader.SetShader("shader\\VS_Shadow.cso", "shader\\PS_Shadow.cso");
	//g_shader.SetShader("shader/VS_Shadow.hlsl", "shader/PS_DepthWrite.hlsl");

	
	// ���b�V�������i�W�I���g���f�[�^�j
	g_staticmesh.Init("asset\\model\\Capoeira.fbx");

	// �`�搶��
	g_staticmeshrenderer.Init(g_staticmesh);

	////�A�j���[�V�������[�h����
	//m_Model = AddComponent<AnimationModel>();

	//m_Model->Load("asset\\model\\Capoeira.fbx");									// animation ok
	//m_Model->LoadAnimation("asset\\model\\Rumba Dancing.fbx", "Idle");
	//m_Model->LoadAnimation("asset\\model\\Capoeira.fbx", "Run");

	//�e
	AddComponent<Shadow>()->SetSize(1.5f);

	m_Scale = Vector3(0.02f, 0.02f, 0.02f);
}

void Human::Uninit()
{
	g_staticmeshrenderer.Uninit();
}

void Human::Update()
{
	//���t���[���A�j���[�V�����X�V
	m_Frame++;
}

void Human::Draw()
{
	//Renderer::ChangeRenderTarget();

	// �f�o�C�X�R���e�L�X�g�擾
	ID3D11DeviceContext* devicecontext;
	devicecontext = Renderer::GetDeviceContext();

	// ���[���h�ϊ��s�񐶐�
	Matrix mtx;
	DX11MakeWorldMatrix(
		mtx,
		m_Scale,							// �X�P�[��
		m_Rotation,							// �p��
		m_Position);						// �ʒu

	// GPU�ɍs����Z�b�g����
	Renderer::SetWorldMatrix(&mtx);

	// �V�F�[�_�[��GPU�ɃZ�b�g
	g_shader.SetGPU();

	// ���f���`��
	g_staticmeshrenderer.Draw();

	ImGui::Begin("AnimationModel");
	// �X���C�_�[
	ImGui::SliderFloat("Blend", &m_BlendRate, 0.0f, 1.0f);
	ImGui::End();

	//Renderer::Begin();
}

void Human::PreDraw()
{
	//m_Model->Update("Idle", m_Frame, "Run", m_Frame, m_BlendRate);
}
