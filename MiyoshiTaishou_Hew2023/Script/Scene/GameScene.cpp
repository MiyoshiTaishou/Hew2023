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
#include"../UI/HitUI.h"

//�R���|�[�l���g
#include"../Component/audio.h"
#include"../Component/SphereCollider.h"

//�p�[�e�B�N��
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
	m_Transition->FadeIn();//�t�F�[�h�C���J�n	

	Customer* cus = AddGameObject<Customer>(Layer1);
	
	BillBoardScore* bill = cus->AddChild<BillBoardScore>();
	bill->AddCount(cus->GetRequests());
	

	//�I�u�W�F�N�g����	
	//AddGameObject<Sky>(Layer1);

	//AddGameObject<YataiObject>(Layer1);

	Manager::InitCount();

	//�����Ă��̍ő吔
	int countMax = 0;
	countMax += GetGameObjects<TakoyakiObject>().size();
	countMax += GetGameObjects<FakeTakoyakiObject>().size();

	Manager::SetCountMax(countMax);
	
	AddGameObject<Camera>(Layer0);	

	//�q�b�g���ɕ\������UI
	AddGameObject<HitUI>(Layer3)->Init(0.0f, 450.0f, 480.0f, 240.0f,
		"../asset\\texture\\�ۂ�.png");

	AddGameObject<HitUI>(Layer3)->Init(800.0f, 0.0f, 480.0f, 240.0f,
		"../asset\\texture\\�ۂ�.png");

	AddGameObject<HitUI>(Layer3)->Init(0.0f, 0.0f, 480.0f, 240.0f,
		"../asset\\texture\\�҂�.png");

	AddGameObject<HitUI>(Layer3)->Init(800.0f, 450.0f, 480.0f, 240.0f,
		"../asset\\texture\\�҂�.png");
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

void GameScene::Draw()
{
	/*write->DrawString("�����Ă���", Vector2(90, 90), D2D1_DRAW_TEXT_OPTIONS_NONE);
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
