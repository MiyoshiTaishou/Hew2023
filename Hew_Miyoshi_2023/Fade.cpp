#include "Fade.h"
#include"shader.h"
#include"sprite.h"

void FadeUI::Init()
{
	AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso", "shader\\PS_FadeShader.cso");
	AddComponent<Sprite>()->Init(0, 0, 1280, 720, "asset\\texture\\field.jpg");

	fade.alpha = m_Alpha;
}

void FadeUI::Update()
{	
	switch (m_State)
	{
	case State::Stop://フェードイン終了
		break;
	case State::In://フェードイン中（透明度を下げていく）
	{
		m_Alpha -= 2.0f / 60.0f;//1秒間に2ずつ透明

		if (m_Alpha < 0.0f)
			m_State = State::Stop;

		break;
	}
	case State::Out://フェードアウト中（透明度を挙げていく）
	{
		m_Alpha += 2.0f / 60.0f;//1秒間に2ずつ透明

		//完全に不透明ならFINISH状態へ
		if (m_Alpha > 1.0f)
			m_State = State::Finish;

		break;
	}
	case State::Finish://フェードアウト終了
		break;
	default:
		break;
	}

	fade.alpha = m_Alpha;

	Renderer::SetFade(fade);
}
