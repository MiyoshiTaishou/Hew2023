#include "main.h"
#include"utility.h"
#include"Result.h"
#include "manager.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "shader.h"
#include "sprite.h"
#include"Transition.h"
#include"audio.h"
#include"Fade.h"
#include"camera.h"

//オブジェクト
#include"sky.h"
#include"Player.h"
#include"Goal.h"
#include"field.h"

using namespace DirectX::SimpleMath;

void Result::Init()
{
	GameObject* titleLogo = AddGameObject<GameObject>(3);// 3はレイヤ番号
	titleLogo->AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso",
		"shader\\PS_BloomBlur.cso");
	titleLogo->AddComponent<Sprite>()->Init(320.0f, 0.0f, 640, 320.0f,
		"asset\\texture\\arigatou.png");

	//オブジェクト生成
	AddGameObject<Sky>(1);
	AddGameObject<Player>(1);
	AddGameObject<Field>(1);

	AddGameObject<Camera>(0);

	//GameObject* titleLogo = AddGameObject<GameObject>(3);// 3はレイヤ番号
	//titleLogo->AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso",
	//	"shader\\PS_BloomBlur.cso");
	//titleLogo->AddComponent<Sprite>()->Init(320.0f, 0.0f, 640, 320.0f,
	//	"asset\\texture\\takoyaki.png");

	GameObject* bgm = AddGameObject<GameObject>(3);
	bgm->AddComponent<Audio>()->Init();
	bgm->GetComponent<Audio>()->Load("asset\\audio\\kiminochikara.wav");
	bgm->GetComponent<Audio>()->Play();

	// チェック完了
	{
		Goal* goal = AddGameObject<Goal>(1);
		goal->SetPosition(Vector3(0.0f, 0.5f, -10.0f));
		goal->SetScale(Vector3(0.5f, 0.5f, 0.5f));
	}

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
	{
		Manager::SetScene<Title>();

		return;
	}

	// ゴールしていないのであれば
	if (!m_Goal)
	{
		Goal* goal = GetGameObject<Goal>();

		// ゴールした際にゴールオブジェクトは削除される
		if (goal == nullptr)
		{
			m_Goal = true;

			// ２秒後にスレッドを生成してフェードアウト開始
			Invoke([=]() { m_Fade->FadeOut(); }, 1000);
		}
	}
}
