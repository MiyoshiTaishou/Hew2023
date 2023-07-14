#pragma once
#include "gameObject.h"
class Transition : public GameObject
{
public:

	//状態
	enum class State
	{
		Stop,//フェードイン終了
		In,//フェードイン
		Out,//フェードアウト
		Finish//フェードアウト終了
	};

private:
	float m_Alpha = 0.0f;
	State m_State = State::Stop;
	class Sprite* m_Sprite{};

public:

	void Init()override;
	void Update()override;

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
};

