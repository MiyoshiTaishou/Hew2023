#include "GameScene.h"

#include"../Sysytem/main.h"
#include"../Sysytem/utility.h"
#include"../Sysytem/input.h"
#include"../Sysytem/manager.h"

//�I�u�W�F�N�g�֌W�w�b�_
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

//�V�[���֌W
#include"ResultScene.h"
#include"Transition.h"

//UI�֌W�w�b�_
#include"../UI/score.h"
#include"../UI/BillBoardScore.h"
#include"../UI/Timer.h"

//�R���|�[�l���g
#include"../Component/audio.h"
#include"../Component/SphereCollider.h"

#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void GameScene::Init()
{	
	//�I�u�W�F�N�g����	
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

		//�U���Ɩ{���������_���ɕ���
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
	m_Transition->FadeIn();//�t�F�[�h�C���J�n	

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
		//�����邩�����Ȃ����𔻒f
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

	//�V�[���J��
	if (m_Transition->GetState() == Transition::State::Stop)
	
	{
		if (Input::GetKeyTrigger(VK_RETURN))
		{
			m_Transition->FadeOut();
		}			
	}	

	//��ʑJ�ڂ��I�����Ă��邩
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
			//�q�ɓ��������Ƃ��ɂ����Ă����������Ă��邩�ŃV�[���J�ڂ��邩���߂�			
			if (Manager::GetCount() >= cus->GetRequests())
			{
				Manager::SetScene<ResultScene>();
				return;
			}
		}
	}
}