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

// �V�[���}�l�[�W���������o�ϐ��̎���
Scene* Manager::m_Scene{}; // ���݂̃V�[��

// �O���[�o���ϐ�
std::list<GameObject*> g_gameobjectlist;

/**
 * @brief �Q�[���}�l�[�W���̏�����
 * @param[in] ap Application�N���X�ւ̃|�C���^
 */
void Manager::Init(Application* ap)
{
    // �^�C�}�𑜓x��1�~���b�ɐݒ�
    timeBeginPeriod(1);

    // �����_���[��������
    Renderer::Init(ap);

    // ImGui�̏�����
    ImGuiManager::ImGuiInit(ap);

    // ���̏�����
    Audio::InitMaster();

    // ���͂̏�����
    Input::Init();

    // Title�������V�[���ɐݒ�
    SetScene<Title>();
}

/**
 * @brief �Q�[���}�l�[�W���̏I������
 */
void Manager::Uninit()
{
    m_Scene->UninitBase();
    delete m_Scene;

    // ImGui�̉��
    ImGuiManager::ImGuiUnInit();

    // 3D���f����S�ĉ��
    ModelRenderer::UnloadAll();

    // �I�[�f�B�I�I��
    Audio::UninitMaster();

    // �^�C�}�𑜓x�����ɖ߂�
    timeEndPeriod(1);
}

/**
 * @brief �Q�[���}�l�[�W���̍X�V����
 * @param[in] d �X�V�ɂ����鎞�ԁi�~���b�j
 */
void Manager::Update(uint64_t d)
{
    Input::Update();

    m_Scene->UpdateBase();
}

/**
 * @brief �Q�[���}�l�[�W���̕`�揈��
 * @param[in] d �`��ɂ����鎞�ԁi�~���b�j
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
