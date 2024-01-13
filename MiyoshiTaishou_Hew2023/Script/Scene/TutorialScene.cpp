#include "TutorialScene.h"

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
#include"../Scene/GameScene.h"
#include"ResultScene.h"
#include"Transition.h"

//UI関係ヘッダ
#include"../UI/score.h"
#include"../UI/BillBoardScore.h"
#include"../UI/Timer.h"

//コンポーネント
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
	//bgm->GetComponent<Audio>()->Load("../asset\\audio\\たこ焼き魂-_Takoyaki-Spirit_.wav");
	bgm->GetComponent<Audio>()->Load("../asset\\audio\\20220515cyouyaku.wav");
	bgm->GetComponent<Audio>()->Play(true);

	m_Transition = AddGameObject<Transition>(Layer3);
	m_Transition->FadeIn();//フェードイン開始	

	//たこ焼きの最大数
	int countMax = 0;
	countMax += GetGameObjects<TakoyakiObject>().size();
	countMax += GetGameObjects<FakeTakoyakiObject>().size();

	Manager::SetCountMax(countMax);

	Player* player = AddGameObject<Player>(Layer1);
	player->SetPosition(Vector3(30, 0, 30));

	AddGameObject<Camera>(Layer0);

	//チュートリアルたこ焼き
	GameObject* Takoyaki = AddGameObject<GameObject>(Layer3);
	Takoyaki->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");
	Takoyaki->AddComponent<Sprite>()->Init(1150,600, 100.0f, 100.0f,
		"../asset\\texture\\2DTakoyaki.png");

	//フォント設定
	FontData* data = new FontData();
	data->fontSize = 28;
	//data->fontWeight = DWRITE_FONT_WEIGHT_BOLD;
	data->fontWeight = DWRITE_FONT_WEIGHT_NORMAL;

	m_Write = new DirectWrite(data);

	m_Write->Init();

	m_TextList = m_Write->ReadTextFile("../MiyoshiTaishou_Hew2023/チュートリアル.txt");
}

void TutorialScene::Update()
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
		Manager::SetScene<GameScene>();
		return;
	}

	//シーン遷移しだしたか
	if (m_Transition->GetState() == Transition::State::Out)
	{
		return;
	}

	//進行度変化させる処理
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

		//移動した
		if (moveCheck)
		{
			m_Progress = MOVE;
			m_TextList.clear();
			m_TextList = m_Write->ReadTextFile("../MiyoshiTaishou_Hew2023/チュートリアルムーブ.txt");

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
				//最後までテキストが描画された
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
			m_TextList = m_Write->ReadTextFile("../MiyoshiTaishou_Hew2023/チュートリアルヒット.txt");

			m_ListIdx = 0;
			m_TexIdx = 0;
			m_Text.clear();
			m_Flame = 0;
		}	
		break;
	}
	case ACTION:
		//最後までテキストが描画された
		if (m_TextList.size() <= m_ListIdx)
		{
			m_Transition->FadeOut();
		}		
		break;
	case END:
	default:
		break;
	}

	//次の文章にいく
	if (Input::GetGamePadTrigger(BUTTON::ABUTTON))
	{
		m_ListIdx++;
		m_TexIdx = 0;
		m_Text.clear();
		m_Flame = 0;
	}

	//最後までテキストが描画された
	if (m_TextList.size() <= m_ListIdx)
	{
		return;
	}

	//文章の末尾まで行った
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
