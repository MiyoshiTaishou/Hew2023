#pragma once

#include"imgui.h"
#include"imgui_impl_win32.h"
#include"imgui_impl_dx11.h"

class Application;

//このヘッダを呼べばImGuiの機能を使えるようになる
class ImGuiManager
{
public:
	//IMGUI関係まとめ
	static void ImGuiInit(Application* ap);
	static void ImGuiUnInit();

	static void Begin();
	static void End();

private:
	static Application* m_Application;
};

