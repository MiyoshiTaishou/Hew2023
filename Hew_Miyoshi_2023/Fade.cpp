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
	case State::Stop://�t�F�[�h�C���I��
		break;
	case State::In://�t�F�[�h�C�����i�����x�������Ă����j
	{
		m_Alpha -= 2.0f / 60.0f;//1�b�Ԃ�2������

		if (m_Alpha < 0.0f)
			m_State = State::Stop;

		break;
	}
	case State::Out://�t�F�[�h�A�E�g���i�����x�������Ă����j
	{
		m_Alpha += 2.0f / 60.0f;//1�b�Ԃ�2������

		//���S�ɕs�����Ȃ�FINISH��Ԃ�
		if (m_Alpha > 1.0f)
			m_State = State::Finish;

		break;
	}
	case State::Finish://�t�F�[�h�A�E�g�I��
		break;
	default:
		break;
	}

	fade.alpha = m_Alpha;

	Renderer::SetFade(fade);
}
