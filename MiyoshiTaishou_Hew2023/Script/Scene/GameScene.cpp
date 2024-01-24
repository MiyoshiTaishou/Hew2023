#include "GameScene.h"

#include"../Sysytem/main.h"
#include"../Sysytem/utility.h"
#include"../Sysytem/input.h"
#include"../Sysytem/manager.h"

//オブジェクト関係ヘッダ
#include"../Object/BoxObject.h"
#include"../Object/Player.h"
#include"../Object/camera.h"
#include"../Object/sky.h"
#include"../Object/field.h"
#include"../Object/Customer.h"
#include"../Object/TakoyakiObject.h"
#include"../Object/FakeTakotaki.h"
#include"../Object/BillBoardObject.h"
#include"../Object/Enemy.h"
#include"../Object/YataiObject.h"

//シーン関係
#include"ResultScene.h"
#include"Transition.h"

//UI関係ヘッダ
#include"../UI/score.h"
#include"../UI/BillBoardScore.h"
#include"../UI/Timer.h"
#include"../UI/HitUI.h"

//コンポーネント
#include"../Component/audio.h"
#include"../Component/SphereCollider.h"

//パーティクル
#include"../Particle/Particle.h"

#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void GameScene::Init()
{				
	Score* score = AddGameObject<Score>(Layer3);	

	AddGameObject<Timer>(Layer3);	

	AddGameObject<Sky>(Layer1);	

	Field* filed = AddGameObject<Field>(Layer1);
	filed->Init(Manager::GetFiledName());

	LoadObjectData(Manager::GetMapName());

	Player* player = AddGameObject<Player>(Layer1);
	player->SetPosition(Vector3(0, 50, 0));
	//player->SetRotation(Vector3(30, 10000, 30));

	//BGMobj
	GameObject* bgm = AddGameObject<GameObject>(3);
	bgm->AddComponent<Audio>()->Init();
	bgm->GetComponent<Audio>()->Load("../asset\\audio\\20220515cyouyaku.wav");
	bgm->GetComponent<Audio>()->Play(true);	

	m_Transition = AddGameObject<Transition>(Layer3);
	m_Transition->FadeIn();//フェードイン開始	

	Customer* cus = AddGameObject<Customer>(Layer1);
	
	BillBoardScore* bill = cus->AddChild<BillBoardScore>();
	bill->AddCount(cus->GetRequests());
	

	//オブジェクト生成	
	//AddGameObject<Sky>(Layer1);

	//AddGameObject<YataiObject>(Layer1);

	Manager::InitCount();

	//たこ焼きの最大数
	int countMax = 0;
	countMax += GetGameObjects<TakoyakiObject>().size();
	countMax += GetGameObjects<FakeTakoyakiObject>().size();

	Manager::SetCountMax(countMax);
	
	AddGameObject<Camera>(Layer0);	

	//ヒット時に表示するUI
	AddGameObject<HitUI>(Layer3)->Init(0.0f, 450.0f, 480.0f, 240.0f,
		"../asset\\texture\\ぽこ.png");

	AddGameObject<HitUI>(Layer3)->Init(800.0f, 0.0f, 480.0f, 240.0f,
		"../asset\\texture\\ぽこ.png");

	AddGameObject<HitUI>(Layer3)->Init(0.0f, 0.0f, 480.0f, 240.0f,
		"../asset\\texture\\ぴた.png");

	AddGameObject<HitUI>(Layer3)->Init(800.0f, 450.0f, 480.0f, 240.0f,
		"../asset\\texture\\ぴた.png");
}

void GameScene::Update()
{	
	Camera* camera = GetGameObject<Camera>();

	std::vector<TakoyakiObject*> stickObj = GetGameObjects<TakoyakiObject>();

	for (auto& obj : stickObj)
	{
		//見えるか見えないかを判断
		Matrix vpmtx;
		vpmtx = camera->GetViewMatrix() * camera->GetProjMatrix();

		bool sts = IsInFrustum(obj->GetPosition(), vpmtx);

		if (!sts)
		{
			obj->SetFrustum(false);
		}
		else
		{
			obj->SetFrustum(true);
		}
	}	

	//シーン遷移
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
		Manager::SetScene<ResultScene>();

		return;
	}

	Player* player = GetGameObject<Player>();
	Customer* cus = GetGameObject<Customer>();

	if (!cus)
	{
		return;
	}

	std::vector<SphereCollider*> col = player->GetComponents<SphereCollider>();

	for (int i = 0; i < col.size(); i++)
	{
		if (col[i]->Hit(cus->GetComponent<SphereCollider>()))
		{
			//客に当たったときにたこ焼きを何個持っているかでシーン遷移するか決める			
			if (Manager::GetCount() >= cus->GetRequests())
			{
				Manager::SetScene<ResultScene>();
				return;
			}
		}
	}	
}

void GameScene::Draw()
{
	/*write->DrawString("たこ焼き魂", Vector2(90, 90), D2D1_DRAW_TEXT_OPTIONS_NONE);
	write->DrawString(text, Vector2(90, 120), D2D1_DRAW_TEXT_OPTIONS_NONE);

	if (flame > 60 && pushText.size() > texIdx)
	{
		
		text.push_back(pushText[texIdx]);
		text.push_back(pushText[texIdx + 1]);
		flame = 0;
		texIdx += 2;
	}

	flame += 2.0f;*/
}
