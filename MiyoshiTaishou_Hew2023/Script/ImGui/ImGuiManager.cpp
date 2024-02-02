#include "ImGuiManager.h"
#include"../Sysytem/Application.h"
#include"../Render/renderer.h"

Application* ImGuiManager::m_Application;

void ImGuiManager::ImGuiInit(Application* ap)
{
	//DIRECT3D構造体にアクセスする
	m_Application = ap;

	//セットアップ
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();	
	ImGui_ImplWin32_Init(m_Application->GetWindow());
	ImGui_ImplDX11_Init(Renderer::GetDevice(),Renderer::GetDeviceContext());
	ImGui::StyleColorsDark();
}

void ImGuiManager::ImGuiUnInit()
{
	//解放
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiManager::Begin()
{
	//IMGuiの描画処理
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::End()
{		
	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
