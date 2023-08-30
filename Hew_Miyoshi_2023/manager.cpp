#include	<list>
#include	"main.h"
#include	"renderer.h"
#include	"manager.h"
#include	"shader.h"
#include	"modelRenderer.h"
#include	"input.h"
#include	"audio.h"
#include	"Game.h"
#include	"Title.h"
#include	"Result.h"
#include	"StageEditor.h"
#include	"fpscontrol.h"

#include"ImGuiManager.h"

// �V�[���}�l�[�W���������o�ϐ��̎���
Scene* Manager::m_Scene{};// ���݃V�[��

// �O���[�o���ϐ�
std::list<GameObject*> g_gameobjectlist;

void Manager::Init(Application* ap)
{
	

	// �^�C�}�𑜓x���P�~���b�ɂ���
	timeBeginPeriod(1);

	// �����_���[��������
	Renderer::Init(ap);

	//ImGui������
	ImGuiManager::ImGuiInit(ap);


	//��������
	Audio::InitMaster();	
	
	//���͏�����
	Input::Init();	

	// Title�������V�[���ɓo�^
	//SetScene<StageEditor>();
	SetScene<Title>();
}

void Manager::Uninit()
{	
	m_Scene->UninitBase();
	delete m_Scene;

	//ImGui���
	ImGuiManager::ImGuiUnInit();

	// �R�c���f����S�ĉ��
	ModelRenderer::UnloadAll();

	//�C���v�b�g�I������
	Input::Uninit();

	//�I�[�f�B�I�I��
	Audio::UninitMaster();

	// �^�C�}�𑜓x�����ɖ߂�
	timeEndPeriod(1);
}

void Manager::Update(uint64_t d)
{
	Input::Update();
	
	m_Scene->UpdateBase();
}

void Manager::Draw(uint64_t d)
{
	Renderer::Begin();
	ImGuiManager::Begin();		

	m_Scene->DrawBase();	

	Renderer::PostProcess();

	float fps = 1000.0f / d;

	ImGui::Begin("FPS");
	ImGui::Text("%fFPS",fps);
	ImGui::End();

	ImGui::Begin("SceneChange");

	if (ImGui::TreeNode(("Create Object ")))
	{
		if (ImGui::Button("TiTle"))
			SetScene<Title>();

		if (ImGui::Button("Game"))
			SetScene<Game>();

		if (ImGui::Button("Result"))
			SetScene<Result>();

		if (ImGui::Button("StageEditor"))
			SetScene<StageEditor>();

		ImGui::TreePop();
	}

	ImGui::End();

	ImGuiManager::End();
	Renderer::End();
}
