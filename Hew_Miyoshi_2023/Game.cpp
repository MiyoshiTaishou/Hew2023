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

//�O�̍��W�ۑ�
Vector3 afterPos;

void Game::Init()
{
	//�I�u�W�F�N�g����
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

	// �G�ǉ�
	AddGameObject<Enemy>(1)->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
	AddGameObject<Enemy>(1)->SetPosition(Vector3(5.0f, 0.0f, 5.0f));
	AddGameObject<Enemy>(1)->SetPosition(Vector3(10.0f, 0.0f, 5.0f));
	AddGameObject<Enemy>(1)->SetPosition(Vector3(15.0f, 0.0f, 5.0f));

	//�G�f�B�^�ō�����V�[�������[�h
	LoadpositionToFile("positions.txt");

	// �`�F�b�N����
	{
		Trampoline* tranpoline = AddGameObject<Trampoline>(1);
		tranpoline->SetPosition(Vector3(0.0f, 0.0f, -20.0f));
		tranpoline->SetScale(Vector3(2.0f, 0.1f, 2.0f));
	}

	// �`�F�b�N����
	{
		DragFloor* floor = AddGameObject<DragFloor>(1);
		floor->SetPosition(Vector3(20.0f, 0.0f, -20.0f));
		floor->SetScale(Vector3(2.0f, 0.1f, 2.0f));
	}

	//m_Transition = AddGameObject<Transition>(3);
	//m_Transition->FadeIn();//�t�F�[�h�C���J�n	

	//BGMobj
	GameObject* bgm = AddGameObject<GameObject>(3);
	bgm->AddComponent<Audio>()->Init();
	bgm->GetComponent<Audio>()->Load("asset\\audio\\maou_12_sekaiga_bokurani_yurerumade.wav");
	bgm->GetComponent<Audio>()->Play();

	//PostProcess* post = AddGameObject<PostProcess>(3);
	m_Fade = AddGameObject<FadeUI>(3);
	m_Fade->FadeIn();//�t�F�[�h�C���J�n	
}

void Game::Update()
{
	//�V�[���J��
	if (m_Fade->GetState() == FadeUI::State::Stop)
		if (Input::GetKeyTrigger(VK_RETURN))
			m_Fade->FadeOut();

	//��ʑJ�ڂ��I�����Ă��邩
	if (m_Fade->GetState() == FadeUI::State::Finish)
		Manager::SetScene<Result>();


	//// �S�[�����Ă��Ȃ��̂ł����
	//if (!m_Goal)
	//{
	//	Goal* goal = GetGameObject<Goal>();

	//	// �S�[�������ۂɃS�[���I�u�W�F�N�g�͍폜�����
	//	if (goal == nullptr)
	//	{
	//		m_Goal = true;

	//		// �Q�b��ɃX���b�h�𐶐����ăt�F�[�h�A�E�g�J�n
	//		Invoke([=]() { m_Fade->FadeOut(); }, 2000);
	//	}
	//}
}

//Game�ł͂Ȃ�scene.h�ɍ쐬���������ǂ�����
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
		// �G���[���b�Z�[�W��\���܂��̓��O�ɋL�^
	}
}
