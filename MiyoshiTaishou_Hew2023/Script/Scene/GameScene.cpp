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

//コンポーネント
#include"../Component/audio.h"
#include"../Component/SphereCollider.h"

#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void GameScene::Init()
{	
	//オブジェクト生成	
	AddGameObject<Sky>(Layer1);
	//AddGameObject<TakoyakiObject>(Layer1);			
	//BillBoardScore* socre = AddGameObject<BillBoardScore>(Layer1);	

	//AddGameObject<BillBoardScore>(Layer1)->AddCount(5);
	AddGameObject<Field>(Layer1);	

	Score* score = AddGameObject<Score>(Layer3);	

	AddGameObject<Timer>(Layer3);

	int idxZ = 1;
	int idxX = 1;

	for (int i = 0; i < MAX_SPHERE; i++)
	{		
		if (idxX > 10)
		{
			idxZ++;
			idxX = 1;
		}

		//偽物と本物をランダムに分類
		int numKind = rand() % 100;

		StickObject* takoyaki;
		if (numKind > 90)
		{
			takoyaki = AddGameObject<FakeTakoyakiObject>(Layer1);
		}
		else
		{
			takoyaki = AddGameObject<TakoyakiObject>(Layer1);
		}
		
		Vector3 pos = Vector3((20.0f * idxX) - 100.0f, 1.0f, (20.0f * idxZ) - 100.0f);
		takoyaki->SetPosition(pos);

		idxX++;
	}


	Player* player = AddGameObject<Player>(Layer1);
	player->SetRotation(Vector3(30, 10000, 30));

	AddGameObject<Camera>(Layer0);

	AddGameObject<Enemy>(Layer1);

	//BGMobj
	GameObject* bgm = AddGameObject<GameObject>(3);
	bgm->AddComponent<Audio>()->Init();
	bgm->GetComponent<Audio>()->Load("../asset\\audio\\20220515cyouyaku.wav");
	bgm->GetComponent<Audio>()->Play(true);	

	m_Transition = AddGameObject<Transition>(Layer3);
	m_Transition->FadeIn();//フェードイン開始	

	AddGameObject<YataiObject>(Layer1);
	Customer* cus = AddGameObject<Customer>(Layer1);
	BillBoardScore* bill = cus->AddChild<BillBoardScore>();
	bill->AddCount(cus->GetRequests());

	Manager::InitCount();
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