#include	<list>
#include	"main.h"
#include	"../Render/renderer.h"
#include	"manager.h"
#include	"../Render/modelRenderer.h"
#include	"fpscontrol.h"
#include"../ImGui/ImGuiManager.h"

//入力
#include	"input.h"

//SE,BGM
#include	"../Component/audio.h"

//シーン
#include"../Scene/GameScene.h"
#include"../Scene/TitleScene.h"
#include"../Scene/StageEditor.h"
#include"../Scene/ResultScene.h"
#include"../Scene/SlopeScene.h"

// シーンマネージャ内メンバ変数の実体
Scene* Manager::m_Scene{};// 現在シーン

int Manager::m_Count = 0;//たこ焼きの数

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
	SetScene<TitleScene>();
	//SetScene<GameScene>();
	//SetScene<ResultScene>();
	//SetScene<SlopeScene>();
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
	//Input::Uninit();

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

	//Renderer::PostProcess();

	float fps = 1000.0f / d;

	ImGui::Begin("FPS");
	ImGui::Text("%fFPS",fps);
	ImGui::End();


	//Debugようシーン遷移
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
