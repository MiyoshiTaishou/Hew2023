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

//UI
#include"../UI/score.h"

using namespace DirectX::SimpleMath;

void ResultScene::Init()
{
	int idxY = 0;
	int idxX = 0;

	//SE�ǉ�
	m_SE[0] = AddGameObject<GameObject>(3);
	Audio* SE = m_SE[0]->AddComponent<Audio>();
	SE->Load("../asset\\audio\\�a���ۂŃh��.wav");
	SE->SetVolume(2.0f);

	m_SE[1] = AddGameObject<GameObject>(3);
	Audio* SE2 = m_SE[1]->AddComponent<Audio>();
	SE2->Load("../asset\\audio\\�a���ۂŃh�h��.wav");
	SE2->SetVolume(5.0f);

	m_SE[2] = AddGameObject<GameObject>(3);
	Audio* SE3 = m_SE[2]->AddComponent<Audio>();	

	for (int i = 3; i < 7; i++)
	{
		m_SE[i] = AddGameObject<GameObject>(Layer3);
		Audio* SE4 = m_SE[i]->AddComponent<Audio>();
		SE4->Load("../asset\\audio\\�ł��グ�ԉ�2.wav");
		SE4->SetVolume(10.0f);
	}	
		
	//���U���g���S
	GameObject* resultLogo = AddGameObject<GameObject>(3);// 3�̓��C���ԍ�
	resultLogo->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");
	resultLogo->AddComponent<Sprite>()->Init(0.0f, 0.0f, 1280, 720.0f,
		"../asset\\texture\\Maturi.jpg");	

	//����������������Ă��̉摜�𐶐�
	for (int i = 0; i < Manager::GetCount(); i++)
	{
		if (idxX > 9)
		{
			idxY++;
			idxX = 0;
		}

		//�����Ă��̐����ǉ�
		GameObject* Takoyaki = AddGameObject<GameObject>(Layer3);
		Takoyaki->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
			"../shader\\unlitTexturePS.cso");
		Takoyaki->AddComponent<Sprite>()->Init(0.0f + (idxX * 50.0f), 600.0f - (idxY * 50.0f), 50.0f, 50.0f,
			"../asset\\texture\\2DTakoyaki.png");
		
		m_Mt.Diffuse = Color(1.0f, 1.0f, 1.0f, 0.0f);
		m_Mt.TextureEnable = true;

		Takoyaki->GetComponent<Sprite>()->SetMaterial(m_Mt);

		m_SpriteObj.push_back(Takoyaki);

		idxX++;
	}

	//���ʔ��\
	m_ResultTex = AddGameObject<GameObject>(Layer3);
	m_ResultTex->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");

	if (Manager::GetCount() < MAX_SPHERE * 0.3f)
	{
		m_ResultTex->AddComponent<Sprite>()->Init(600, 200, 700.0f, 481.5f,
			"../asset\\texture\\SyouMori.png");

		SE3->Load("../asset\\audio\\�j���u�I�[�b�I�v.wav");
		SE3->SetVolume(5.0f);
	}	
	else if(Manager::GetCount() < MAX_SPHERE * 0.6f)
	{
		m_ResultTex->AddComponent<Sprite>()->Init(600, 200, 700.0f, 481.5f,
			"../asset\\texture\\TyuuMori.png");

		SE3->Load("../asset\\audio\\�j�O�u�C�G�[�C�I�v.wav");
		SE3->SetVolume(5.0f);
	}
	else if (Manager::GetCount() < MAX_SPHERE)
	{
		m_ResultTex->AddComponent<Sprite>()->Init(600, 200, 700.0f, 481.5f,
			"../asset\\texture\\OoMori.png");

		SE3->Load("../asset\\audio\\�����ς�.wav");
		SE3->SetVolume(5.0f);
	}
	else if (Manager::GetCount() == MAX_SPHERE)
	{
		m_ResultTex->AddComponent<Sprite>()->Init(600, 200, 700.0f, 481.5f,
			"../asset\\texture\\Takoyakinngu.png");

		SE3->Load("../asset\\audio\\�����ς�.wav");
		SE3->SetVolume(5.0f);
	}

	m_Mt.Diffuse.w = 0.0f;
	m_ResultTex->GetComponent<Sprite>()->SetMaterial(m_Mt);

	//Score* score = AddGameObject<Score>(Layer3);
	//score->Init(400, 230, 50, 50);
	//score->AddCount(Manager::GetCount());

	//Score* scoreRate = AddGameObject<Score>(Layer3);
	//scoreRate->Init(400, 480, 40, 40);

	////�ǂ̒��x�Ƃꂽ��
	//float rate = ((float)Manager::GetCount() /  (float)MAX_SPHERE);
	//int percent = rate * 100;
	//scoreRate->AddCount(percent);

	//�I�u�W�F�N�g����
	//AddGameObject<Sky>(Layer1);
	//AddGameObject<Player>(Layer1);
	//AddGameObject<Field>(Layer1);

	//AddGameObject<Camera>(Layer0);

	//BGM�ǉ�
	GameObject* bgm = AddGameObject<GameObject>(Layer3);
	bgm->AddComponent<Audio>()->Init();
	bgm->GetComponent<Audio>()->Load("../asset\\audio\\20220515cyouyaku.wav");
	bgm->GetComponent<Audio>()->Play();
	bgm->GetComponent<Audio>()->SetVolume(0.5f);

	m_Transition = AddGameObject<Transition>(3);
	m_Transition->FadeIn();//�t�F�[�h�C���J�n
}

void ResultScene::Update()
{
	//��ʑJ�ڂ��I�����Ă��邩
	if (m_Transition->GetState() == Transition::State::Finish)
	{
		Manager::SetScene<TitleScene>();

		return;
	}

	//�X�L�b�v���ꂽ�炱�̏������s��Ȃ�
	if (m_Skip)
	{
		return;
	}

	if (m_Transition->GetState() == Transition::State::Stop)
	{
		if (Input::GetKeyTrigger(VK_RETURN))
		{
			m_Transition->FadeOut();
		}

		if (Input::GetGamePad(BUTTON::ABUTTON))
		{			
			//�����ꂽ���C�ɕ\��
			m_Mt.Diffuse.w = 1.0f;
			for (auto& obj : m_SpriteObj)
			{
				obj->GetComponent<Sprite>()->SetMaterial(m_Mt);
			}
			//�����ɂ����ς������
			m_ResultTex->GetComponent<Sprite>()->SetMaterial(m_Mt);			
			m_SE[1]->GetComponent<Audio>()->Play();
			m_SE[2]->GetComponent<Audio>()->Play();
			
			m_Skip = true;
			Invoke([=]() {m_Transition->FadeOut(); }, 1000);			
		}
	}	

	//�����Ă������Ԃɕ\�����Ă�������
	if (m_SpriteObj.size() == 0)
	{
		return;
	}

	//���S�ɕ\���o�����玟��
	if (m_Mt.Diffuse.w > 1.0f)
	{
		m_SE[0]->GetComponent<Audio>()->Play();
		m_Mt.Diffuse.w = 0.0f;
		m_SpriteNo++;
	}
	else
	{	
		//���X�ɉ�������
		m_Mt.Diffuse.w += m_SpriteNo / 10 * 0.1f + 0.1f;
	}	

	//�Ō�܂ł����Ă���`�悵���猋�ʔ��\�e�N�X�`������������
	if (m_SpriteNo >= m_SpriteObj.size())
	{		
		m_Skip = true;
		m_Mt.Diffuse.w = 1.0f;
	
		//�����ɂ����ς������
		Audio* SE = m_SE[1]->GetComponent<Audio>();
		Audio* SE2 = m_SE[2]->GetComponent<Audio>();

		if (Manager::GetCount() == MAX_SPHERE)
		{
			for (int i = 3; i < 7; i++)
			{
				Audio* SE3 = m_SE[3]->GetComponent<Audio>();
				Invoke([=]() {SE3->Play(); }, 1000 + i * 500);
			}
		}

		Sprite* sprite = m_ResultTex->GetComponent<Sprite>();
		Invoke([=]() {sprite->SetMaterial(m_Mt); }, 1000);
		Invoke([=]() {SE->Play(); }, 1000);
		Invoke([=]() {SE2->Play(); }, 1000);	

		Invoke([=]() {m_Transition->FadeOut(); }, 10000);

		return;
	}

	m_SpriteObj[m_SpriteNo]->GetComponent<Sprite>()->SetMaterial(m_Mt);
	
}
