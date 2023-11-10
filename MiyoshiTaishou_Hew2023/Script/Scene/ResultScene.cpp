#include "ResultScene.h"

//�V�X�e��
#include"../Sysytem/input.h"
#include"../Sysytem/manager.h"

//�I�u�W�F�N�g
#include"../Object/sky.h"
#include"../Object/Player.h"
#include"../Object/field.h"
#include"../Object/camera.h"
#include"Transition.h"

//�R���|�[�l���g
#include"../Component/shader.h"
#include"../Component/sprite.h"
#include"../Component/audio.h"

//�V�[��
#include"TitleScene.h"

void ResultScene::Init()
{
	//���U���g���S
	GameObject* resultLogo = AddGameObject<GameObject>(3);// 3�̓��C���ԍ�
	resultLogo->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\PS_BloomBlur.cso");
	resultLogo->AddComponent<Sprite>()->Init(320.0f, 0.0f, 640, 320.0f,
		"../asset\\texture\\arigatou.png");

	//�I�u�W�F�N�g����
	AddGameObject<Sky>(Layer1);
	AddGameObject<Player>(Layer1);
	AddGameObject<Field>(Layer1);

	AddGameObject<Camera>(Layer0);

	//BGM�ǉ�
	GameObject* bgm = AddGameObject<GameObject>(Layer3);
	bgm->AddComponent<Audio>()->Init();
	bgm->GetComponent<Audio>()->Load("../asset\\audio\\kiminochikara.wav");
	bgm->GetComponent<Audio>()->Play();

	m_Transition = AddGameObject<Transition>(3);
	m_Transition->FadeIn();//�t�F�[�h�C���J�n
}

void ResultScene::Update()
{
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
		Manager::SetScene<TitleScene>();

		return;
	}
}
