#include "HitUI.h"

//シーン
#include"../Scene/scene.h"

//マネージャー
#include"../Sysytem/manager.h"

//コンポーネント
#include"../Component/shader.h"
#include"../Component/sprite.h"

//IMGUI
#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void HitUI::Init()
{
	
}

void HitUI::Init(int x, int y, int Width, int Height, const char* TextureName)
{
	this->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");

	m_Sprite = this->AddComponent<Sprite>();
	m_Sprite->Init(x, y, Width, Height,
		TextureName);

	m_MT.TextureEnable = true;
	m_MT.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
}

void HitUI::Update()
{
	switch (m_State)
	{
	case Stop:
		m_Color.w = 0.0f;
		m_MT.Diffuse = m_Color;
		m_Sprite->SetMaterial(m_MT);
		break;
	case AddRun:

		//徐々に緩やかになる処理
		m_Color.w += (-m_Time * -m_Time) + (2 * m_Time);
		m_MT.Diffuse = m_Color;
		m_MT.Ambient = m_Color;
		m_Sprite->SetMaterial(m_MT);

		if (m_Color.w > 0.9f)
		{
			m_State = SubRun;
			m_Time = 0.0f;
			m_Color.w = 1.0f;
		}

		m_Time += m_AddTime;

		break;
	case SubRun:

		//徐々に速くなる処理
		m_Color.w -= m_Time * m_Time;
		m_MT.Diffuse = m_Color;
		m_Sprite->SetMaterial(m_MT);

		if (m_Color.w < 0.1f)
		{
			m_State = Stop;
			m_Time = 0.0f;
			m_Color.w = 0.0f;
		}

		m_Time += m_AddTime;

		break;
	default:
		break;
	}
}

void HitUI::Draw()
{
#ifdef _DEBUG

	ImGui::Begin("UI");
	if (ImGui::Button("START"))
	{
		this->Indication();
	}

	ImGui::Text("Color %f,%f,%f,%f", m_Color.x, m_Color.y, m_Color.z,m_Color.w);
	ImGui::End();

#endif // _DEBUG

}

void HitUI::Indication()
{
	//稼働中ならしない
	if (m_State != Stop)
	{
		return;
	}

	//処理を開始する
	m_State = AddRun;

	//0~10で値を取って0.1~1にする
	float R = rand() % 11;
	R *= 0.1f;
	float G = rand() % 11;
	G *= 0.1f;
	float B = rand() % 11;
	B *= 0.1f;

	//ランダムな色に設定
	m_Color.x = R;
	m_Color.y = G;
	m_Color.z = B;

	//動きが単調にならないように値をランダムに増加させる
	m_AddTime += (rand() % 10 + 1) * 0.001f;

	m_Time = 0.0f;
}
