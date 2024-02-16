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
#include"../Scene/TitleScene.h"
#include"../Scene/GameScene.h"
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
#include"../Component/shader.h"
#include"../Component/sprite.h"

#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void TutorialScene::Init()
{
	Score* score = AddGameObject<Score>(Layer3);

	AddGameObject<Sky>(Layer1)->Init("../asset\\model\\sky3.obj");

	Field* filed = AddGameObject<Field>(Layer1);
	filed->Init("../asset/map/Title.csv");	

	//BGMobj
	for (int i = 0; i < 3; i++)
	{
		m_BGM[i] = AddGameObject<GameObject>(Layer3);
		m_BGM[i]->AddComponent<Audio>()->Init();

		if (Manager::GetBGMList()[i] != "../asset\\audio\\None.wav")
		{
			m_BGM[i]->GetComponent<Audio>()->Load(Manager::GetBGMList()[i].c_str());
			m_BGM[i]->GetComponent<Audio>()->SetVolume(5.0f);
		}
	}

	//BGMが何もなければ
	if (Manager::GetBGMList()[0] == "../asset\\audio\\None.wav")
	{
		//BGM追加
		m_BGM[3] = AddGameObject<GameObject>(Layer3);
		m_BGM[3]->AddComponent<Audio>()->Init();
		m_BGM[3]->GetComponent<Audio>()->Load("../asset\\audio\\跳躍.wav");
		m_BGM[3]->GetComponent<Audio>()->SetVolume(5.0f);
		m_BGM[3]->GetComponent<Audio>()->Play();
	}
	else
	{
		m_BGM[0]->GetComponent<Audio>()->Play(false);
	}

	//ヒット時に表示するUI
	AddGameObject<HitUI>(Layer3)->Init(0.0f, 450.0f, 480.0f, 240.0f,
		"../asset\\texture\\ぽこ.png");

	AddGameObject<HitUI>(Layer3)->Init(800.0f, 0.0f, 480.0f, 240.0f,
		"../asset\\texture\\ぽこ.png");

	AddGameObject<HitUI>(Layer3)->Init(0.0f, 0.0f, 480.0f, 240.0f,
		"../asset\\texture\\ぴた.png");

	AddGameObject<HitUI>(Layer3)->Init(800.0f, 450.0f, 480.0f, 240.0f,
		"../asset\\texture\\ぴた.png");

	//チュートリアルたこ焼き
	GameObject* Takoyaki = AddGameObject<GameObject>(Layer3);
	Takoyaki->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");
	Takoyaki->AddComponent<Sprite>()->Init(1150, 600, 100.0f, 100.0f,
		"../asset\\texture\\2DTakoyaki.png");

	//チュートリアルUI
	m_UIobj = AddGameObject<GameObject>(Layer3);	
	m_UIobj->AddComponent<Sprite>()->Init(-50, 450, 1250.0f, 200.0f,
		"../asset\\texture\\吹き出し.png");

	m_Transition = AddGameObject<Transition>(Layer3);
	m_Transition->FadeIn();//フェードイン開始	

	//たこ焼きの最大数
	int countMax = 0;
	countMax += GetGameObjects<TakoyakiObject>().size();
	countMax += GetGameObjects<FakeTakoyakiObject>().size();

	Manager::SetCountMax(countMax);

	Player* player = AddGameObject<Player>(Layer1);
	player->SetPosition(Vector3(0, 40, -140));

	AddGameObject<Camera>(Layer0);	

	//フォント設定
	FontData* data = new FontData();
	data->fontSize = 25;
	data->fontWeight = DWRITE_FONT_WEIGHT_BOLD;	
	data->Color = D2D1::ColorF(1.0f, 1.0f, 0.0f, 1.0f);

	m_Write = new DirectWrite(data);

	m_Write->Init();

	m_TextList = m_Write->ReadTextFile("../asset/text/チュートリアル.txt");
}

void TutorialScene::Uninit()
{
	m_Write->Uninit();
	delete m_Write;
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
	if (m_Transition->GetState() == Transition::State::Finish && !m_BGM[m_BGMIndex]->GetComponent<Audio>()->GetFade())
	{
		Manager::SetScene<TitleScene>();
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
			m_TextList = m_Write->ReadTextFile("../asset/text/チュートリアルムーブ.txt");

			m_ListIdx = 0;
			m_TexIdx = 0;
			m_Text.clear();
			m_Flame = 0;

			m_TextEnd = false;
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
			m_TextList = m_Write->ReadTextFile("../asset/text/チュートリアルヒット.txt");

			m_ListIdx = 0;
			m_TexIdx = 0;
			m_Text.clear();
			m_Flame = 0;

			m_TextEnd = false;
		}	
		break;
	}
	case ACTION:
		//最後までテキストが描画された
		if (m_TextList.size() <= m_ListIdx)
		{
			m_Transition->FadeOut();
			m_BGM[m_BGMIndex]->GetComponent<Audio>()->Stop();
		}		
		break;
	case END:
	default:
		break;
	}

	if (m_TextEnd)
	{
		m_UIobj->GetComponent<Sprite>()->SetView(false);
		return;
	}

	//次の文章にいく
	if (m_TextList[m_ListIdx].size() < m_TexIdx)
	{
		if (Input::GetGamePadTrigger(BUTTON::BBUTTON))
		{			
			m_ListIdx++;
			m_TexIdx = 0;
			m_Text.clear();
			m_Flame = 0;
		}
	}
	else
	{
		if (Input::GetGamePadTrigger(BUTTON::BBUTTON))
		{
			while (m_TextList[m_ListIdx].size() > m_TexIdx)
			{
				m_Text.push_back(m_TextList[m_ListIdx][m_TexIdx]);
				m_Flame = 0;
				m_TexIdx += 1;
			}
		}
	}

	//最後までテキストが描画された
	if (m_TextList.size() <= m_ListIdx)
	{
		m_TextEnd = true;
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

	m_UIobj->GetComponent<Sprite>()->SetView(true);

	//何もない場合のBGMなら
	if (m_BGMIndex == 3)
	{
		return;
	}

	//初期文字なら再生しない
	if (Manager::GetBGMList()[m_BGMIndex] == "../asset\\audio\\None.wav")
	{
		return;
	}

	//最後まで行ったら最初に
	if (m_BGMIndex > 2)
	{
		m_BGMIndex = 0;
	}

	//BGMが再生終了したら次再生
	if (!m_BGM[m_BGMIndex]->GetComponent<Audio>()->IsSoundPlaying())
	{
		m_BGMIndex++;

		//初期文字なら再生しない
		if (Manager::GetBGMList()[m_BGMIndex] != "../asset\\audio\\None.wav")
		{
			m_BGM[m_BGMIndex]->GetComponent<Audio>()->Play(false);
		}
	}
}

void TutorialScene::Draw()
{	
	m_Write->DrawString(m_Text, Vector2(10, 400), D2D1_DRAW_TEXT_OPTIONS_NONE);		
}
