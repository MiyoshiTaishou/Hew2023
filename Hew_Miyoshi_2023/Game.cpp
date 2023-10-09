#include "Game.h"
#include"main.h"
#include"utility.h"

#include"sprite.h"
#include"audio.h"
#include"shader.h"
#include"Transition.h"
#include"BoxCollider.h"

#include"polygon2D.h"
#include"field.h"
#include"camera.h"
#include"gameObject.h"
#include"Player.h"
#include"box.h"
#include"cylinder.h"
#include "manager.h"
#include "input.h"
#include"Result.h"
#include"Goal.h"
#include"Enemy.h"
#include"sky.h"
#include"Stage.h"
#include"Trampoline.h"
#include"DragFloor.h"
#include"Human.h"
#include"Octopus.h"

#include"score.h"
#include"Timer.h"
#include"PostProcess.h"
#include"Fade.h"
#include"ScaleUI.h"
#include <fstream>

#include<SimpleMath.h>
using namespace DirectX::SimpleMath;

//前の座標保存
Vector3 afterPos;

void Game::Init()
{
	//オブジェクト生成
	AddGameObject<Sky>(1);
	AddGameObject<Player>(1);
	AddGameObject<Field>(1);
	AddGameObject<Score>(3);
	AddGameObject<Timer>(3);
	AddGameObject<Human>(1);
	AddGameObject<Octopus>(1);
	//AddGameObject<ScaleUI>(3);

	AddGameObject<Camera>(0);
	//Camera* Cameraobj = GetGameObject<Camera>();
	//Cameraobj->GetComponent<BackCameraComponent>()->SetTarget(*GetGameObject<Player>());

	// 敵追加
	AddGameObject<Enemy>(1)->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
	AddGameObject<Enemy>(1)->SetPosition(Vector3(5.0f, 0.0f, 5.0f));
	AddGameObject<Enemy>(1)->SetPosition(Vector3(10.0f, 0.0f, 5.0f));
	AddGameObject<Enemy>(1)->SetPosition(Vector3(15.0f, 0.0f, 5.0f));

	//エディタで作ったシーンをロード
	LoadpositionToFile("positions.txt");

	// チェック完了
	{
		Trampoline* tranpoline = AddGameObject<Trampoline>(1);
		tranpoline->SetPosition(Vector3(0.0f, 0.0f, -20.0f));
		tranpoline->SetScale(Vector3(2.0f, 0.1f, 2.0f));
	}

	// チェック完了
	{
		DragFloor* floor = AddGameObject<DragFloor>(1);
		floor->SetPosition(Vector3(20.0f, 0.0f, -20.0f));
		floor->SetScale(Vector3(2.0f, 0.1f, 2.0f));
	}

	//m_Transition = AddGameObject<Transition>(3);
	//m_Transition->FadeIn();//フェードイン開始	

	//BGMobj
	GameObject* bgm = AddGameObject<GameObject>(3);
	bgm->AddComponent<Audio>()->Init();
	bgm->GetComponent<Audio>()->Load("asset\\audio\\maou_12_sekaiga_bokurani_yurerumade.wav");
	bgm->GetComponent<Audio>()->Play();

	//PostProcess* post = AddGameObject<PostProcess>(3);
	m_Fade = AddGameObject<FadeUI>(3);
	m_Fade->FadeIn();//フェードイン開始	
}

void Game::Update()
{
	//シーン遷移
	if (m_Fade->GetState() == FadeUI::State::Stop)
		if (Input::GetKeyTrigger(VK_RETURN))
			m_Fade->FadeOut();

	//画面遷移が終了しているか
	if (m_Fade->GetState() == FadeUI::State::Finish)
		Manager::SetScene<Result>();


	//// ゴールしていないのであれば
	//if (!m_Goal)
	//{
	//	Goal* goal = GetGameObject<Goal>();

	//	// ゴールした際にゴールオブジェクトは削除される
	//	if (goal == nullptr)
	//	{
	//		m_Goal = true;

	//		// ２秒後にスレッドを生成してフェードアウト開始
	//		Invoke([=]() { m_Fade->FadeOut(); }, 2000);
	//	}
	//}
}

//Gameではなくscene.hに作成した方が良さそう
void Game::LoadpositionToFile(const std::string& filename)
{
	std::ifstream inputFile(filename);

	if (inputFile.is_open())
	{
		InfoObjData data;
		int classKind;
		while (inputFile >> data.pos.x >> data.pos.y >> data.pos.z
			>> data.scale.x >> data.scale.y >> data.scale.z
			>> data.rot.x >> data.rot.y >> data.rot.z
			>> classKind)
		{
			switch (classKind)
			{
			case CLASS::BOX:
			{
				Box* box = AddGameObject<Box>(1);
				box->SetPosition(data.pos);
				box->SetRotation(data.rot);
				box->SetScale(data.scale);

				break;
			}
			case CLASS::ENEMY:
			{
				Enemy* enemy = AddGameObject<Enemy>(1);
				enemy->SetPosition(data.pos);
				enemy->SetRotation(data.rot);
				enemy->SetScale(data.scale);

				break;
			}
			default:
				break;
			}
		}

		inputFile.close();
	}
	else
	{
		// エラーメッセージを表示またはログに記録
	}
}
