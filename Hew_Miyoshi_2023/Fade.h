#pragma once
#include "gameObject.h"
#include"renderer.h"
class FadeUI : public GameObject
{
public:
	void Init();	
	void Update();

	//状態
	enum class State
	{
		Stop,//フェードイン終了
		In,//フェードイン
		Out,//フェードアウト
		Finish//フェードアウト終了
	};

	State GetState() { return m_State; }

	//フェードイン初期処理
	void FadeIn()
	{
		m_Alpha = 1.0f;
		m_State = State::In;
	}

	//フェードアウト初期処理
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

