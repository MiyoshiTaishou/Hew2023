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

// シーンマネージャ内メンバ変数の実体
Scene* Manager::m_Scene{};// 現在シーン

// グローバル変数
std::list<GameObject*> g_gameobjectlist;

void Manager::Init(Application* ap)
{
	

	// タイマ解像度を１ミリ秒にする
	timeBeginPeriod(1);

	// レンダラーを初期化
	Renderer::Init(ap);

	//ImGui初期化
	ImGuiManager::ImGuiInit(ap);


	//音初期化
	Audio::InitMaster();	
	
	//入力初期化
	Input::Init();	

	// Titleを初期シーンに登録
	//SetScene<StageEditor>();
	SetScene<Title>();
}

void Manager::Uninit()
{	
	m_Scene->UninitBase();
	delete m_Scene;

	//ImGui解放
	ImGuiManager::ImGuiUnInit();

	// ３Ｄモデルを全て解放
	ModelRenderer::UnloadAll();

	//インプット終了処理
	Input::Uninit();

	//オーディオ終了
	Audio::UninitMaster();

	// タイマ解像度を元に戻す
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
