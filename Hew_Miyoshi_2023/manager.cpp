#pragma once
#include <list>
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "shader.h"
#include "modelRenderer.h"
#include "input.h"
#include "audio.h"
#include "Game.h"
#include "Title.h"
#include "Result.h"
#include "StageEditor.h"
#include "fpscontrol.h"

#include "ImGuiManager.h"

// シーンマネージャ内メンバ変数の実体
Scene* Manager::m_Scene{}; // 現在のシーン

// グローバル変数
std::list<GameObject*> g_gameobjectlist;

/**
 * @brief ゲームマネージャの初期化
 * @param[in] ap Applicationクラスへのポインタ
 */
void Manager::Init(Application* ap)
{
    // タイマ解像度を1ミリ秒に設定
    timeBeginPeriod(1);

    // レンダラーを初期化
    Renderer::Init(ap);

    // ImGuiの初期化
    ImGuiManager::ImGuiInit(ap);

    // 音の初期化
    Audio::InitMaster();

    // 入力の初期化
    Input::Init();

    // Titleを初期シーンに設定
    SetScene<Title>();
}

/**
 * @brief ゲームマネージャの終了処理
 */
void Manager::Uninit()
{
    m_Scene->UninitBase();
    delete m_Scene;

    // ImGuiの解放
    ImGuiManager::ImGuiUnInit();

    // 3Dモデルを全て解放
    ModelRenderer::UnloadAll();

    // オーディオ終了
    Audio::UninitMaster();

    // タイマ解像度を元に戻す
    timeEndPeriod(1);
}

/**
 * @brief ゲームマネージャの更新処理
 * @param[in] d 更新にかかる時間（ミリ秒）
 */
void Manager::Update(uint64_t d)
{
    Input::Update();

    m_Scene->UpdateBase();
}

/**
 * @brief ゲームマネージャの描画処理
 * @param[in] d 描画にかかる時間（ミリ秒）
 */
void Manager::Draw(uint64_t d)
{
    Renderer::Begin();
    ImGuiManager::Begin();

    m_Scene->DrawBase();

    Renderer::PostProcess();

    float fps = 1000.0f / d;

    ImGui::Begin("FPS");
    ImGui::Text("%f FPS", fps);
    ImGui::End();

    ImGui::Begin("SceneChange");

    if (ImGui::TreeNode(("Create Object ")))
    {
        if (ImGui::Button("Title"))
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
