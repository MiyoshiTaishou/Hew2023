#pragma once
#include "gameObject.h"
#include"renderer.h"
class FadeUI : public GameObject
{
public:
	void Init();	
	void Update();

	//���
	enum class State
	{
		Stop,//�t�F�[�h�C���I��
		In,//�t�F�[�h�C��
		Out,//�t�F�[�h�A�E�g
		Finish//�t�F�[�h�A�E�g�I��
	};

	State GetState() { return m_State; }

	//�t�F�[�h�C����������
	void FadeIn()
	{
		m_Alpha = 1.0f;
		m_State = State::In;
	}

	//�t�F�[�h�A�E�g��������
	void FadeOut()
	{
		m_Alpha = 0.0f;
		m_State = State::Out;
	}

private:
	Fade fade;
	float time = 0.0f;	

	float m_Alpha = 0.0f;
	State m_State = State::Stop;
	class Sprite* m_Sprite{};
};

