#include "Result.h"
#include "main.h"
#include "manager.h"
#include "input.h"
#include "title.h"
#include "shader.h"
#include "sprite.h"
#include"Transition.h"
#include"Fade.h"

void Result::Init()
{
	GameObject* titleLogo = AddGameObject<GameObject>(3);// 3はレイヤ番号
	titleLogo->AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso",
		"shader\\unlitTexturePS.cso");
	titleLogo->AddComponent<Sprite>()->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		"asset\\texture\\result.jpg");

	//m_Transition = AddGameObject<Transition>(3);
	//m_Transition->FadeIn();//フェードイン開始
	m_Fade = AddGameObject<FadeUI>(3);
	m_Fade->FadeIn();
}

void Result::Update()
{
	if (m_Fade->GetState() == FadeUI::State::Stop)
		if (Input::GetKeyTrigger(VK_RETURN))
			m_Fade->FadeOut();

	//画面遷移が終了しているか
	if (m_Fade->GetState() == FadeUI::State::Finish)
		Manager::SetScene<Title>();
}
