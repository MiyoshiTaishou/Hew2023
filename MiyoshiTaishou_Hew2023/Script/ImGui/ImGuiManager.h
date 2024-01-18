#pragma once

#include"imgui.h"
#include"imgui_impl_win32.h"
#include"imgui_impl_dx11.h"

class Application;

//���̃w�b�_���Ăׂ�ImGui�̋@�\���g����悤�ɂȂ�
class ImGuiManager
{
public:
	//IMGUI�֌W�܂Ƃ�
	static void ImGuiInit(Application* ap);
	static void ImGuiUnInit();

	static void Begin();
	static void End();

private:
	static Application* m_Application;
};

