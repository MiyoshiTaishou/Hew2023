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
#include"../Scene/GameScene.h"
#include"ResultScene.h"
#include"Transition.h"

//UI�֌W�w�b�_
#include"../UI/score.h"
#include"../UI/BillBoardScore.h"
#include"../UI/Timer.h"

//�R���|�[�l���g
#include"../Component/audio.h"
#include"../Component/SphereCollider.h"
#include"../Component/shader.h"
#include"../Component/sprite.h"

#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void TutorialScene::Init()
{
	Score* score = AddGameObject<Score>(Layer3);

	AddGameObject<Field>(Layer1);

	//BGMobj
	GameObject* bgm = AddGameObject<GameObject>(3);
	bgm->AddComponent<Audio>()->Init();
	//bgm->GetComponent<Audio>()->Load("../asset\\audio\\�����Ă���-_Takoyaki-Spirit_.wav");
	bgm->GetComponent<Audio>()->Load("../asset\\audio\\20220515cyouyaku.wav");
	bgm->GetComponent<Audio>()->Play(true);

	m_Transition = AddGameObject<Transition>(Layer3);
	m_Transition->FadeIn();//�t�F�[�h�C���J�n	

	//�����Ă��̍ő吔
	int countMax = 0;
	countMax += GetGameObjects<TakoyakiObject>().size();
	countMax += GetGameObjects<FakeTakoyakiObject>().size();

	Manager::SetCountMax(countMax);

	Player* player = AddGameObject<Player>(Layer1);
	player->SetPosition(Vector3(30, 0, 30));

	AddGameObject<Camera>(Layer0);

	//�`���[�g���A�������Ă�
	GameObject* Takoyaki = AddGameObject<GameObject>(Layer3);
	Takoyaki->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");
	Takoyaki->AddComponent<Sprite>()->Init(1150,600, 100.0f, 100.0f,
		"../asset\\texture\\2DTakoyaki.png");

	//�t�H���g�ݒ�
	FontData* data = new FontData();
	data->fontSize = 28;
	//data->fontWeight = DWRITE_FONT_WEIGHT_BOLD;
	data->fontWeight = DWRITE_FONT_WEIGHT_NORMAL;

	m_Write = new DirectWrite(data);

	m_Write->Init();

	m_TextList = m_Write->ReadTextFile("../MiyoshiTaishou_Hew2023/�`���[�g���A��.txt");
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
		Manager::SetScene<GameScene>();
		return;
	}

	//�V�[���J�ڂ���������
	if (m_Transition->GetState() == Transition::State::Out)
	{
		return;
	}

	//�i�s�x�ω������鏈��
	switch (m_Progress)
	{
	case START:
	{
		bool moveCheck = false;

		if (Input::GetGamePad(BUTTON::LDOWN))
		{
			moveCheck = true;
		}
		if (Input::GetGamePad(BUTTON::LUP))
		{
			moveCheck = true;
		}
		if (Input::GetGamePad(BUTTON::LLEFT))
		{
			moveCheck = true;
		}
		if (Input::GetGamePad(BUTTON::LRIGHT))
		{
			moveCheck = true;
		}

		//�ړ�����
		if (moveCheck)
		{
			m_Progress = MOVE;
			m_TextList.clear();
			m_TextList = m_Write->ReadTextFile("../MiyoshiTaishou_Hew2023/�`���[�g���A�����[�u.txt");

			m_ListIdx = 0;
			m_TexIdx = 0;
			m_Text.clear();
			m_Flame = 0;
		}

		break;
	}
	case MOVE:
	{	
		TakoyakiObject* obj = GetGameObject<TakoyakiObject>();

		Score* score = GetGameObject<Score>();
		
		if (score->GetCount() == 0)
		{
			if (!obj)
			{
				//�Ō�܂Ńe�L�X�g���`�悳�ꂽ
				if (m_TextList.size() <= m_ListIdx)
				{
					for (int i = 0; i < 30; i++)
					{
						TakoyakiObject* obj = AddGameObject<TakoyakiObject>(Layer1);
						obj->SetPosition((Vector3(10, 0, 0)* i) - (Vector3(150, 0, 0)));
					}					
				}
			}
		}
		else
		{
			m_Progress = ACTION;

			m_TextList.clear();
			m_TextList = m_Write->ReadTextFile("../MiyoshiTaishou_Hew2023/�`���[�g���A���q�b�g.txt");

			m_ListIdx = 0;
			m_TexIdx = 0;
			m_Text.clear();
			m_Flame = 0;
		}	
		break;
	}
	case ACTION:
		//�Ō�܂Ńe�L�X�g���`�悳�ꂽ
		if (m_TextList.size() <= m_ListIdx)
		{
			m_Transition->FadeOut();
		}		
		break;
	case END:
	default:
		break;
	}

	//���̕��͂ɂ���
	if (Input::GetGamePadTrigger(BUTTON::ABUTTON))
	{
		m_ListIdx++;
		m_TexIdx = 0;
		m_Text.clear();
		m_Flame = 0;
	}

	//�Ō�܂Ńe�L�X�g���`�悳�ꂽ
	if (m_TextList.size() <= m_ListIdx)
	{
		return;
	}

	//���̖͂����܂ōs����
	if (m_TextList[m_ListIdx].size() < m_TexIdx)
	{
		return;
	}

	if (m_Flame > 60)
	{
		m_Text.push_back(m_TextList[m_ListIdx][m_TexIdx]);
		m_Flame = 0;
		m_TexIdx += 1;
	}

	m_Flame += 60.0f;
}

void TutorialScene::Draw()
{	
	m_Write->DrawString(m_Text, Vector2(10, 600), D2D1_DRAW_TEXT_OPTIONS_NONE);		
}
