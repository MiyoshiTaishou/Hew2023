#include "TutorialScene.h"

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

void TutorialScene::Init()
{
	Score* score = AddGameObject<Score>(Layer3);

	AddGameObject<Field>(Layer1);

	//BGMobj
	GameObject* bgm = AddGameObject<GameObject>(3);
	bgm->AddComponent<Audio>()->Init();
	bgm->GetComponent<Audio>()->Load("../asset\\audio\\�����Ă���-_Takoyaki-Spirit_.wav");
	bgm->GetComponent<Audio>()->Play(true);

	m_Transition = AddGameObject<Transition>(Layer3);
	m_Transition->FadeIn();//�t�F�[�h�C���J�n	

	//�����Ă��̍ő吔
	int countMax = 0;
	countMax += GetGameObjects<TakoyakiObject>().size();
	countMax += GetGameObjects<FakeTakoyakiObject>().size();

	Manager::SetCountMax(countMax);

	Player* player = AddGameObject<Player>(Layer1);
	//player->SetRotation(Vector3(30, 10000, 30));

	AddGameObject<Camera>(Layer0);

	FontData* data = new FontData();
	data->fontSize = 60;
	data->fontWeight = DWRITE_FONT_WEIGHT_BOLD;

	write = new DirectWrite(data);

	write->Init();

	textList = write->ReadTextFile("../MiyoshiTaishou_Hew2023/�`���[�g���A��.txt");
}

void TutorialScene::Update()
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
}

void TutorialScene::Draw()
{
	write->DrawString(text, Vector2(90, 120), D2D1_DRAW_TEXT_OPTIONS_NONE);

	if (textList.size() == listIdx)
	{
		return;
	}

	if (textList[listIdx].size() < texIdx)
	{
		listIdx++;
		texIdx = 0;
		text.clear();
	}

	if (flame > 60)
	{
		text.push_back(textList[listIdx][texIdx]);
		//text.push_back(pushText[texIdx + 1]);
		flame = 0;
		texIdx += 1;
	}

	flame += 60.0f;
}
