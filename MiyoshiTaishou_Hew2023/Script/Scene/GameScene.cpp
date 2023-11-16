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
#include"../Object/BillBoardObject.h"

//シーン関係
#include"ResultScene.h"
#include"Transition.h"

//UI関係ヘッダ
#include"../UI/score.h"
#include"../UI/BillBoardScore.h"

//コンポーネント
#include"../Component/audio.h"
#include"../Component/SphereCollider.h"

#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

#define MAX_SPHERE 10

void GameScene::Init()
{
	//オブジェクト生成
	LoadObjectData("Obj.csv");
	AddGameObject<Sky>(Layer1);
	//AddGameObject<TakoyakiObject>(Layer1);	
	Customer* cus = AddGameObject<Customer>(Layer1);
	AddGameObject<Player>(Layer1);
	//BillBoardScore* socre = AddGameObject<BillBoardScore>(Layer1);
	BillBoardScore* bill = cus->AddChild<BillBoardScore>();	
	bill->SetPosition(Vector3(0, 20, 10));	
	bill->AddCount(cus->GetRequests());

	//AddGameObject<BillBoardScore>(Layer1)->AddCount(5);
	//AddGameObject<Field>(Layer1);

	AddGameObject<Camera>(Layer0);

	AddGameObject<Score>(Layer3);

	for (int i = 0; i < MAX_SPHERE; i++)
	{
		TakoyakiObject* takoyaki = AddGameObject<TakoyakiObject>(Layer1);
		Vector3 pos = Vector3(5.0f * i, 1.0f, 1.0f);
		takoyaki->SetPosition(pos);
	}

	//BGMobj
	GameObject* bgm = AddGameObject<GameObject>(3);
	bgm->AddComponent<Audio>()->Init();
	bgm->GetComponent<Audio>()->Load("../asset\\audio\\maou_12_sekaiga_bokurani_yurerumade.wav");
	bgm->GetComponent<Audio>()->Play();

	m_Transition = AddGameObject<Transition>(Layer3);
	m_Transition->FadeIn();//フェードイン開始		
}

void GameScene::Update()
{
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

	SphereCollider* col = player->GetComponent<SphereCollider>();

	if(col->Hit(cus->GetComponent<SphereCollider>()))
	{
		//客に当たったときにたこ焼きを何個持っているかでシーン遷移するか決める			
		if (GetGameObject<Score>()->GetCount() > cus->GetRequests())
		{
			Manager::SetScene<ResultScene>();
			return;
		}				
	}
}