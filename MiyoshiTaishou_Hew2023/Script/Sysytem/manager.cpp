#include	<list>
#include	"main.h"
#include	"../Render/renderer.h"
#include	"manager.h"
#include	"../Render/modelRenderer.h"
#include	"fpscontrol.h"
#include"../ImGui/ImGuiManager.h"

//����
#include	"input.h"

//SE,BGM
#include	"../Component/audio.h"

//�V�[��
#include"../Scene/GameScene.h"
#include"../Scene/TitleScene.h"
#include"../Scene/StageEditor.h"
#include"../Scene/ResultScene.h"
#include"../Scene/SlopeScene.h"

// �V�[���}�l�[�W���������o�ϐ��̎���
Scene* Manager::m_Scene{};// ���݃V�[��

int Manager::m_Count = 0;//�����Ă��̐�

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
	SetScene<TitleScene>();
	//SetScene<GameScene>();
	//SetScene<ResultScene>();
	//SetScene<SlopeScene>();
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
	//Input::Uninit();

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

	//Renderer::PostProcess();

	float fps = 1000.0f / d;

	ImGui::Begin("FPS");
	ImGui::Text("%fFPS",fps);
	ImGui::End();


	//Debug�悤�V�[���J��
	ImGui::Begin("SceneChange");

	if (ImGui::TreeNode(("Scene")))
	{
		if (ImGui::Button("TiTle"))
			SetScene<TitleScene>();

		if (ImGui::Button("Game"))
			SetScene<GameScene>();

		if (ImGui::Button("Result"))
			SetScene<ResultScene>();

		if (ImGui::Button("StageEditor"))
			SetScene<StageEditor>();

		ImGui::TreePop();
	}

	ImGui::End();

	ImGuiManager::End();
	Renderer::End();
}
