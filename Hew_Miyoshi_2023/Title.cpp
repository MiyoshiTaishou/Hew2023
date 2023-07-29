#include "main.h"
#include "manager.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "shader.h"
#include "sprite.h"
#include"Transition.h"
#include"audio.h"
#include"Fade.h"

void Title::Init()
{
	GameObject* titleLogo = AddGameObject<GameObject>(3);// 3�̓��C���ԍ�
	titleLogo->AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso",
		"shader\\unlitTexturePS.cso");
	titleLogo->AddComponent<Sprite>()->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		"asset\\texture\\title.jpg");

	GameObject* bgm = AddGameObject<GameObject>(3);
	bgm->AddComponent<Audio>()->Init();
	bgm->GetComponent<Audio>()->Load("asset\\audio\\bgm.wav");
	bgm->GetComponent<Audio>()->Play();

	//m_Transition = AddGameObject<Transition>(3);
	//m_Transition->FadeIn();//�t�F�[�h�C���J�n
	m_Fade = AddGameObject<FadeUI>(3);
	m_Fade->FadeIn();
}

void Title::Update()
{
	
	if (m_Fade->GetState() == FadeUI::State::Stop)
		if (Input::GetKeyTrigger(VK_RETURN))
			m_Fade->FadeOut();

	//��ʑJ�ڂ��I�����Ă��邩
	if (m_Fade->GetState() == FadeUI::State::Finish)
		Manager::SetScene<Game>();
}
