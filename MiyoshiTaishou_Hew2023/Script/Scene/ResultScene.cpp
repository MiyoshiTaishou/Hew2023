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

using namespace DirectX::SimpleMath;

void ResultScene::Init()
{
	int idxY = 0;
	int idxX = 0;

	//SE追加
	m_SE[0] = AddGameObject<GameObject>(3);
	Audio* SE = m_SE[0]->AddComponent<Audio>();
	SE->Load("../asset\\audio\\和太鼓でドン.wav");
	SE->SetVolume(2.0f);

	m_SE[1] = AddGameObject<GameObject>(3);
	Audio* SE2 = m_SE[1]->AddComponent<Audio>();
	SE2->Load("../asset\\audio\\和太鼓でドドン.wav");
	SE2->SetVolume(5.0f);

	m_SE[2] = AddGameObject<GameObject>(3);
	Audio* SE3 = m_SE[2]->AddComponent<Audio>();	

	for (int i = 3; i < 7; i++)
	{
		m_SE[i] = AddGameObject<GameObject>(Layer3);
		Audio* SE4 = m_SE[i]->AddComponent<Audio>();
		SE4->Load("../asset\\audio\\打ち上げ花火2.wav");
		SE4->SetVolume(10.0f);
	}	
		
	//リザルトロゴ
	GameObject* resultLogo = AddGameObject<GameObject>(3);// 3はレイヤ番号
	resultLogo->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");
	resultLogo->AddComponent<Sprite>()->Init(0.0f, 0.0f, 1280, 720.0f,
		"../asset\\texture\\Maturi.jpg");	

	//取った数だけたこ焼きの画像を生成
	for (int i = 0; i < Manager::GetCount(); i++)
	{
		if (idxX > 9)
		{
			idxY++;
			idxX = 0;
		}

		//たこ焼きの数分追加
		GameObject* Takoyaki = AddGameObject<GameObject>(Layer3);
		Takoyaki->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
			"../shader\\unlitTexturePS.cso");
		Takoyaki->AddComponent<Sprite>()->Init(0.0f + (idxX * 50.0f), 600.0f - (idxY * 50.0f), 50.0f, 50.0f,
			"../asset\\texture\\2DTakoyaki.png");
		
		m_Mt.Diffuse = Color(1.0f, 1.0f, 1.0f, 0.0f);
		m_Mt.TextureEnable = true;

		Takoyaki->GetComponent<Sprite>()->SetMaterial(m_Mt);

		m_SpriteObj.push_back(Takoyaki);

		idxX++;
	}

	//結果発表
	m_ResultTex = AddGameObject<GameObject>(Layer3);
	m_ResultTex->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");

	if (Manager::GetCount() < MAX_SPHERE * 0.3f)
	{
		m_ResultTex->AddComponent<Sprite>()->Init(600, 200, 700.0f, 481.5f,
			"../asset\\texture\\SyouMori.png");

		SE3->Load("../asset\\audio\\男声「オーッ！」.wav");
		SE3->SetVolume(5.0f);
	}	
	else if(Manager::GetCount() < MAX_SPHERE * 0.6f)
	{
		m_ResultTex->AddComponent<Sprite>()->Init(600, 200, 700.0f, 481.5f,
			"../asset\\texture\\TyuuMori.png");

		SE3->Load("../asset\\audio\\男衆「イエーイ！」.wav");
		SE3->SetVolume(5.0f);
	}
	else if (Manager::GetCount() < MAX_SPHERE)
	{
		m_ResultTex->AddComponent<Sprite>()->Init(600, 200, 700.0f, 481.5f,
			"../asset\\texture\\OoMori.png");

		SE3->Load("../asset\\audio\\あっぱれ.wav");
		SE3->SetVolume(5.0f);
	}
	else if (Manager::GetCount() == MAX_SPHERE)
	{
		m_ResultTex->AddComponent<Sprite>()->Init(600, 200, 700.0f, 481.5f,
			"../asset\\texture\\Takoyakinngu.png");

		SE3->Load("../asset\\audio\\あっぱれ.wav");
		SE3->SetVolume(5.0f);
	}

	m_Mt.Diffuse.w = 0.0f;
	m_ResultTex->GetComponent<Sprite>()->SetMaterial(m_Mt);

	//Score* score = AddGameObject<Score>(Layer3);
	//score->Init(400, 230, 50, 50);
	//score->AddCount(Manager::GetCount());

	//Score* scoreRate = AddGameObject<Score>(Layer3);
	//scoreRate->Init(400, 480, 40, 40);

	////どの程度とれたか
	//float rate = ((float)Manager::GetCount() /  (float)MAX_SPHERE);
	//int percent = rate * 100;
	//scoreRate->AddCount(percent);

	//オブジェクト生成
	//AddGameObject<Sky>(Layer1);
	//AddGameObject<Player>(Layer1);
	//AddGameObject<Field>(Layer1);

	//AddGameObject<Camera>(Layer0);

	//BGM追加
	GameObject* bgm = AddGameObject<GameObject>(Layer3);
	bgm->AddComponent<Audio>()->Init();
	bgm->GetComponent<Audio>()->Load("../asset\\audio\\20220515cyouyaku.wav");
	bgm->GetComponent<Audio>()->Play();
	bgm->GetComponent<Audio>()->SetVolume(0.5f);

	m_Transition = AddGameObject<Transition>(3);
	m_Transition->FadeIn();//フェードイン開始
}

void ResultScene::Update()
{
	//画面遷移が終了しているか
	if (m_Transition->GetState() == Transition::State::Finish)
	{
		Manager::SetScene<TitleScene>();

		return;
	}

	//スキップされたらこの処理を行わない
	if (m_Skip)
	{
		return;
	}

	if (m_Transition->GetState() == Transition::State::Stop)
	{
		if (Input::GetKeyTrigger(VK_RETURN))
		{
			m_Transition->FadeOut();
		}

		if (Input::GetGamePad(BUTTON::ABUTTON))
		{			
			//押されたら一気に表示
			m_Mt.Diffuse.w = 1.0f;
			for (auto& obj : m_SpriteObj)
			{
				obj->GetComponent<Sprite>()->SetMaterial(m_Mt);
			}
			//ここにあっぱれを入れる
			m_ResultTex->GetComponent<Sprite>()->SetMaterial(m_Mt);			
			m_SE[1]->GetComponent<Audio>()->Play();
			m_SE[2]->GetComponent<Audio>()->Play();
			
			m_Skip = true;
			Invoke([=]() {m_Transition->FadeOut(); }, 1000);			
		}
	}	

	//たこ焼きを順番に表示していく処理
	if (m_SpriteObj.size() == 0)
	{
		return;
	}

	//完全に表示出来たら次へ
	if (m_Mt.Diffuse.w > 1.0f)
	{
		m_SE[0]->GetComponent<Audio>()->Play();
		m_Mt.Diffuse.w = 0.0f;
		m_SpriteNo++;
	}
	else
	{	
		//徐々に加速する
		m_Mt.Diffuse.w += m_SpriteNo / 10 * 0.1f + 0.1f;
	}	

	//最後までたこ焼きを描画したら結果発表テクスチャを差し込む
	if (m_SpriteNo >= m_SpriteObj.size())
	{		
		m_Skip = true;
		m_Mt.Diffuse.w = 1.0f;
	
		//ここにあっぱれを入れる
		Audio* SE = m_SE[1]->GetComponent<Audio>();
		Audio* SE2 = m_SE[2]->GetComponent<Audio>();

		if (Manager::GetCount() == MAX_SPHERE)
		{
			for (int i = 3; i < 7; i++)
			{
				Audio* SE3 = m_SE[3]->GetComponent<Audio>();
				Invoke([=]() {SE3->Play(); }, 1000 + i * 500);
			}
		}

		Sprite* sprite = m_ResultTex->GetComponent<Sprite>();
		Invoke([=]() {sprite->SetMaterial(m_Mt); }, 1000);
		Invoke([=]() {SE->Play(); }, 1000);
		Invoke([=]() {SE2->Play(); }, 1000);	

		Invoke([=]() {m_Transition->FadeOut(); }, 10000);

		return;
	}

	m_SpriteObj[m_SpriteNo]->GetComponent<Sprite>()->SetMaterial(m_Mt);
	
}
