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

//UI
#include"../UI/score.h"

void ResultScene::Init()
{
	//リザルトロゴ
	GameObject* resultLogo = AddGameObject<GameObject>(3);// 3はレイヤ番号
	resultLogo->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");
	resultLogo->AddComponent<Sprite>()->Init(0.0f, 0.0f, 1280, 720.0f,
		"../asset\\texture\\result.jpg");

	Score* score = AddGameObject<Score>(Layer3);
	score->Init(400, 210, 100, 100);
	score->AddCount(Manager::GetCount());

	Score* scoreRate = AddGameObject<Score>(Layer3);
	scoreRate->Init(400, 410, 100, 100);

	//どの程度とれたか
	float rate = ((float)Manager::GetCount() /  (float)MAX_SPHERE);
	int percent = rate * 100;
	scoreRate->AddCount(percent);

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
