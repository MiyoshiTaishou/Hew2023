#include "Game.h"
#include"main.h"
#include"utility.h"

#include"sprite.h"
#include"audio.h"
#include"BulletComponent.h"
#include"shader.h"
#include"Transition.h"
#include"BoxCollider.h"
#include"BackCameraComponent.h"

#include"polygon2D.h"
#include"field.h"
#include"camera.h"
#include"gameObject.h"
#include"Player.h"
#include"box.h"
#include"cylinder.h"
#include"Bullet.h"
#include "manager.h"
#include "input.h"
#include"Result.h"
#include"Goal.h"
#include"Enemy.h"
#include"sky.h"
#include"Stage.h"

#include"score.h"
#include"Timer.h"
#include"PostProcess.h"
#include"Fade.h"
#include"ScaleUI.h"

#include<SimpleMath.h>
using namespace DirectX::SimpleMath;

//前の座標保存
Vector3 afterPos;

void Game::Init()
{
	AddGameObject<Sky>(1);
	AddGameObject<Player>(1);
	AddGameObject<Field>(1);	
	AddGameObject<Score>(3);
	AddGameObject<Timer>(3);
	AddGameObject<ScaleUI>(3);

	AddGameObject<Camera>(0);
	//Camera* Cameraobj = GetGameObject<Camera>();
	//Cameraobj->GetComponent<BackCameraComponent>()->SetTarget(*GetGameObject<Player>());

	// 敵追加
	AddGameObject<Enemy>(1)->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
	AddGameObject<Enemy>(1)->SetPosition(Vector3(5.0f, 0.0f, 5.0f));
	AddGameObject<Enemy>(1)->SetPosition(Vector3(10.0f, 0.0f, 5.0f));
	AddGameObject<Enemy>(1)->SetPosition(Vector3(15.0f, 0.0f, 5.0f));

	// チェック完了
	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(Vector3(-5.0f, 0.0f, 5.0f));
		box->SetScale(Vector3(3.0f, 1.0f, 3.0f));
	}

	// チェック完了
	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(Vector3(-11.0f, 0.0f, 5.0f));
		box->SetScale(Vector3(3.0f, 2.0f, 3.0f));
	}

	// チェック完了
	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(Vector3(-11.0f, 0.0f, 11.0f));
		box->SetScale(Vector3(3.0f, 3.0f, 3.0f));
	}

	// チェック完了
	{
		Cylinder* cylinder = AddGameObject<Cylinder>(1);
		cylinder->SetPosition(Vector3(-11.0f, 0.0f, 20.0f));
		cylinder->SetScale(Vector3(3.0f, 6.0f, 3.0f));
	}

	// チェック完了
	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(Vector3(0.0f, 0.0f, 20.0f));
		box->SetScale(Vector3(9.0f, 3.0f, 1.0f));
	}

	// チェック完了
	{
		Cylinder* cylinder = AddGameObject<Cylinder>(1);
		cylinder->SetPosition(Vector3(11.0f, 0.0f, 20.0f));
		cylinder->SetScale(Vector3(3.0f, 6.0f, 3.0f));
	}

	// チェック完了
	{
		Goal* goal = AddGameObject<Goal>(1);
		goal->SetPosition(Vector3(0.0f, 0.5f, -10.0f));
		goal->SetScale(Vector3(0.5f, 0.5f, 0.5f));
	}	

	//m_Transition = AddGameObject<Transition>(3);
	//m_Transition->FadeIn();//フェードイン開始	
	
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
