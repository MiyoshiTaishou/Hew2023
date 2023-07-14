#pragma once
#include "gameObject.h"
class Transition : public GameObject
{
public:

	//���
	enum class State
	{
		Stop,//�t�F�[�h�C���I��
		In,//�t�F�[�h�C��
		Out,//�t�F�[�h�A�E�g
		Finish//�t�F�[�h�A�E�g�I��
	};

private:
	float m_Alpha = 0.0f;
	State m_State = State::Stop;
	class Sprite* m_Sprite{};

public:

	void Init()override;
	void Update()override;

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
};

