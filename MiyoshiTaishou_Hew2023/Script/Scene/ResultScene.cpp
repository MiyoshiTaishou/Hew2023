#include "ResultScene.h"

//システム
#include"../Sysytem/input.h"
#include"../Sysytem/manager.h"

//オブジェクト
#include"../Object/sky.h"
#include"../Object/Player.h"
#include"../Object/field.h"
#include"../Object/camera.h"
#include"Transition.h"

//コンポーネント
#include"../Component/shader.h"
#include"../Component/sprite.h"
#include"../Component/audio.h"

//シーン
#include"TitleScene.h"

void ResultScene::Init()
{
	//リザルトロゴ
	GameObject* resultLogo = AddGameObject<GameObject>(3);// 3はレイヤ番号
	resultLogo->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\PS_BloomBlur.cso");
	resultLogo->AddComponent<Sprite>()->Init(320.0f, 0.0f, 640, 320.0f,
		"../asset\\texture\\arigatou.png");

	//オブジェクト生成
	AddGameObject<Sky>(Layer1);
	AddGameObject<Player>(Layer1);
	AddGameObject<Field>(Layer1);

	AddGameObject<Camera>(Layer0);

	//BGM追加
	GameObject* bgm = AddGameObject<GameObject>(Layer3);
	bgm->AddComponent<Audio>()->Init();
	bgm->GetComponent<Audio>()->Load("../asset\\audio\\kiminochikara.wav");
	bgm->GetComponent<Audio>()->Play();

	m_Transition = AddGameObject<Transition>(3);
	m_Transition->FadeIn();//フェードイン開始
}

void ResultScene::Update()
{
	if (m_Transition->GetState() == Transition::State::Stop)
	{
		if (Input::GetKeyTrigger(VK_RETURN))
		{
			m_Transition->FadeOut();
		}
	}

	//画面遷移が終了しているか
	if (m_Transition->GetState() == Transition::State::Finish)
	{
		Manager::SetScene<TitleScene>();

		return;
	}
}
