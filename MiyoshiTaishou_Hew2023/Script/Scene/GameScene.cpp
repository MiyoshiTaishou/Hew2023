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
#include"../Object/BillBoardObject.h"

//�V�[���֌W
#include"ResultScene.h"
#include"Transition.h"

//UI�֌W�w�b�_
#include"../UI/score.h"

//�R���|�[�l���g
#include"../Component/audio.h"
#include"../Component/SphereCollider.h"

#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

#define MAX_BOX 10

void GameScene::Init()
{
	//�I�u�W�F�N�g����
	LoadObjectData("Obj.csv");
	AddGameObject<Sky>(Layer1);
	AddGameObject<TakoyakiObject>(Layer1);	
	AddGameObject<Customer>(Layer1);
	AddGameObject<Player>(Layer1);
	//AddGameObject<BillBoardObject>(Layer1);
	AddGameObject<Field>(Layer1);

	AddGameObject<Camera>(Layer0);

	AddGameObject<Score>(Layer3);

	/*for (int i = 0; i < MAX_BOX; i++)
	{
		BoxObject* box = AddGameObject<BoxObject>(Layer1);
		Vector3 pos = Vector3(5.0f * i, 1.0f, 1.0f);
		box->SetPosition(pos);
	}*/

	//BGMobj
	GameObject* bgm = AddGameObject<GameObject>(3);
	bgm->AddComponent<Audio>()->Init();
	bgm->GetComponent<Audio>()->Load("../asset\\audio\\maou_12_sekaiga_bokurani_yurerumade.wav");
	bgm->GetComponent<Audio>()->Play();

	m_Transition = AddGameObject<Transition>(Layer3);
	m_Transition->FadeIn();//�t�F�[�h�C���J�n		
}

void GameScene::Update()
{
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

	SphereCollider* col = player->GetComponent<SphereCollider>();

	if(col->Hit(cus->GetComponent<SphereCollider>()))
	{
		Manager::SetScene<ResultScene>();

		return;
	}
}