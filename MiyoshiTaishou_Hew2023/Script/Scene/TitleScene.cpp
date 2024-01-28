#include "TitleScene.h"

//�V�X�e��
#include"../Sysytem/input.h"
#include"../Sysytem/manager.h"

//�I�u�W�F�N�g
#include"../Object/sky.h"
#include"../Object/Player.h"
#include"../Object/field.h"
#include"../Object/camera.h"
#include"../Object/BillBoardObject.h"
#include"../Object/YataiObject.h"
#include"../Object/TreeObject.h"
#include"../Object/YakisobaObject.h"
#include"../Object/KasuteraObject.h"
#include"../Object/CarObject.h"
#include"Transition.h"

//�R���|�[�l���g
#include"../Component/shader.h"
#include"../Component/sprite.h"
#include"../Component/audio.h"
#include"../Component/SphereCollider.h"
#include"../Component/RootChaise.h"

//�V�[��
#include"GameScene.h"
#include"TutorialScene.h"

//UI
#include"../UI/score.h"
#include"../UI/HitUI.h"

using namespace DirectX::SimpleMath;

void TitleScene::Init()
{
	Score* score = AddGameObject<Score>(Layer3);

	//�I�u�W�F�N�g����
	AddGameObject<Sky>(Layer1)->Init("../asset\\model\\sky2.obj");
	Field* filed = AddGameObject<Field>(Layer1);
	filed->Init("../asset/map/Title.csv");

	Player* player = AddGameObject<Player>(Layer1);
	player->SetPosition(Vector3(0, 40, -140));

	//�I�u�W�F�N�g���[�h
	LoadObjectData("../asset/map/titleMap.csv");	

	AddGameObject<Camera>(Layer0);	
	
	//BGM
	GameObject* bgm = AddGameObject<GameObject>(Layer3);
	bgm->AddComponent<Audio>()->Init();
	bgm->GetComponent<Audio>()->Load("../asset\\audio\\20220515cyouyaku.wav");
	bgm->GetComponent<Audio>()->Play();		

	//�^�C�g����ʂ悤�t�F�[�h
	m_TitleSprite[0] = AddGameObject<GameObject>(Layer3);
	m_TitleSprite[0]->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");
	m_TitleSprite[0]->AddComponent<Sprite>()->Init(0.0f, 0.0f, 1280.0f, 720.0f,
		"../asset\\texture\\white.jpg");
	
	m_TitleMt.TextureEnable = true;
	m_TitleMt.Diffuse = Color(1.0f, 1.0f, 1.0f, 0.5f);

	m_TitleSprite[0]->GetComponent<Sprite>()->SetMaterial(m_TitleMt);

	//�^�C�g���摜
	m_TitleSprite[1] = AddGameObject<GameObject>(Layer3);// 3�̓��C���ԍ�
	m_TitleSprite[1]->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");
	m_TitleSprite[1]->AddComponent<Sprite>()->Init(320.0f, 100.0f, 640, 320.0f,
		"../asset\\texture\\takoyaki.png");

	//�^�C�g���{�^���摜
	m_TitleSprite[2] = AddGameObject<GameObject>(Layer3);// 3�̓��C���ԍ�
	m_TitleSprite[2]->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\unlitTexturePS.cso");
	m_TitleSprite[2]->AddComponent<Sprite>()->Init(320.0f, 300.0f, 640, 320.0f,
		"../asset\\texture\\AnyKey.png");

	m_AnyKeyMT.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_AnyKeyMT.TextureEnable = true;

	m_TitleSprite[2]->GetComponent<Sprite>()->SetMaterial(m_AnyKeyMT);

	//�q�b�g���ɕ\������UI
	AddGameObject<HitUI>(Layer3)->Init(0.0f, 450.0f, 480.0f, 240.0f,
		"../asset\\texture\\�ۂ�.png");

	AddGameObject<HitUI>(Layer3)->Init(800.0f, 0.0f, 480.0f, 240.0f,
		"../asset\\texture\\�ۂ�.png");

	AddGameObject<HitUI>(Layer3)->Init(0.0f, 0.0f, 480.0f, 240.0f,
		"../asset\\texture\\�҂�.png");

	AddGameObject<HitUI>(Layer3)->Init(800.0f, 450.0f, 480.0f, 240.0f,
		"../asset\\texture\\�҂�.png");
	
	//�t�F�[�h�p�摜
	GameObject* Niji = AddGameObject<GameObject>(Layer3);// 3�̓��C���ԍ�		
	Niji->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\PS_AlphaFade.cso");
	Niji->AddComponent<Sprite>()->Init(0.0f, 0.0f, 1280, 720.0f,
		"../asset\\texture\\Niji.jpg");

	//�X�e�[�W�I���摜
	BillBoardObject* bill = AddGameObject<BillBoardObject>(Layer1);
	bill->Init("../asset/texture/���l�O.png");
	bill->AddComponent<SphereCollider>()->SetRadius(6.0f);	
	bill->SetPosition(Vector3(100, 10, 50));

	BillBoardObject* bill2 = AddGameObject<BillBoardObject>(Layer1);	
	bill2->Init("../asset/texture/Tutorial.png");
	bill2->AddComponent<SphereCollider>()->SetRadius(6.0f);
	bill2->SetPosition(Vector3(0, 20, 50));

	BillBoardObject* bill3 = AddGameObject<BillBoardObject>(Layer1);
	bill3->Init("../asset/texture/��l�O.png");
	bill3->AddComponent<SphereCollider>()->SetRadius(6.0f);
	bill3->SetPosition(Vector3(-100, 10, 50));

	BillBoardObject* bill4 = AddGameObject<BillBoardObject>(Layer1);
	bill4->Init("../asset/texture/�ʓV�t����.png");
	bill4->AddComponent<SphereCollider>()->SetRadius(6.0f);
	bill4->SetPosition(Vector3(-100, 10, -50));

	BillBoardObject* bill5 = AddGameObject<BillBoardObject>(Layer1);
	bill5->Init("../asset/texture/���y������.png");
	bill5->AddComponent<SphereCollider>()->SetRadius(6.0f);
	bill5->SetPosition(Vector3(100, 10, -50));
	
	//�����t�F�[�h������
	//���t���[�����Ƃ̎��Ԃ��X�V		
	ZeroMemory(&timeBufferDesc, sizeof(timeBufferDesc));

	timeBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	timeBufferDesc.ByteWidth = sizeof(float) * 4; // ���ԃf�[�^�̃T�C�Y�i4��float�j
	timeBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	timeBufferDesc.CPUAccessFlags = 0;
	timeBufferDesc.MiscFlags = 0;
	
	ZeroMemory(&timeBufferData, sizeof(timeBufferData));
	float timeData[4] = { currentTime, 0.0f, 0.0f, 0.0f }; // ���ԃf�[�^���i�[����ꍇ
	timeBufferData.pSysMem = timeData;

	// �萔�o�b�t�@���쐬
	Renderer::GetDevice()->CreateBuffer(&timeBufferDesc, &timeBufferData, &timeBuffer);

	// �V�F�[�_�[�Ɏ��ԃf�[�^�𑗐M
	ID3D11Buffer* timeBuffers[] = { timeBuffer };
	Renderer::GetDeviceContext()->VSSetConstantBuffers(10, 1, timeBuffers); // ���_�V�F�[�_�[�ɓn���ꍇ
	Renderer::GetDeviceContext()->PSSetConstantBuffers(10, 1, timeBuffers); // �s�N�Z���V�F�[�_�[�ɓn���ꍇ

	//SE�ݒ�
	m_SEObj = AddGameObject<GameObject>(Layer3);
	m_SEObj->AddComponent<Audio>()->Init();
	m_SEObj->GetComponent<Audio>()->Load("../asset\\audio\\�j���u�I�[�b�I�v.wav");
	m_SEObj->GetComponent<Audio>()->SetVolume(5.0f);

	m_Transition = AddGameObject<Transition>(3);
	m_Transition->FadeIn();//�t�F�[�h�C���J�n		
}

void TitleScene::Update()
{
	//���Ԍo�ߏ���
	currentTime -= 0.005f;

	if (currentTime < 0.0f)
	{
		currentTime = 0.0f;
	}

	ZeroMemory(&timeBufferData, sizeof(timeBufferData));
	float timeData[4] = { currentTime, 0.0f, 0.0f, 0.0f }; // ���ԃf�[�^���i�[����ꍇ
	timeBufferData.pSysMem = timeData;

	// �萔�o�b�t�@���쐬
	Renderer::GetDevice()->CreateBuffer(&timeBufferDesc, &timeBufferData, &timeBuffer);

	// �V�F�[�_�[�Ɏ��ԃf�[�^�𑗐M
	ID3D11Buffer* timeBuffers[] = { timeBuffer };
	Renderer::GetDeviceContext()->VSSetConstantBuffers(10, 1, timeBuffers); // ���_�V�F�[�_�[�ɓn���ꍇ
	Renderer::GetDeviceContext()->PSSetConstantBuffers(10, 1, timeBuffers); // �s�N�Z���V�F�[�_�[�ɓn���ꍇ

	Player* player = GetGameObject<Player>();	

#ifdef _DEBUG
	if (m_Transition->GetState() == Transition::State::Stop)
	{
		if (Input::GetKeyTrigger(VK_RETURN))
		{
			m_Transition->FadeOut();
		}
	}
#endif // _DEBUG

	if (m_Transition->GetState() == Transition::State::Out)
	{
		player->SetController(false);
		return;
	}

	//��ʑJ�ڂ��I�����Ă��邩
	if (m_Transition->GetState() == Transition::State::Finish)
	{		
		switch (m_Select)
		{
		case TUTORIAL:
			Manager::SetScene<TutorialScene>();
			break;
		case GAME1:
			Manager::SetFiledName("../asset/map/GameMap1-1.csv");
			Manager::SetMapName("../asset/map/1-1.csv");
			Manager::SetSkyName("../asset\\model\\sky2.obj");
			Manager::SetScene<GameScene>();			
			break;
		case GAME2:		
			Manager::SetFiledName("../asset/map/GameMap1-2.csv");
			Manager::SetMapName("../asset/map/1-2.csv");
			Manager::SetSkyName("../asset\\model\\sky3.obj");
			Manager::SetScene<GameScene>();			
			break;
		case GAME3:
			Manager::SetFiledName("../asset/map/GameMap1-3.csv");
			Manager::SetMapName("../asset/map/1-3.csv");
			Manager::SetSkyName("../asset\\model\\sky.obj");
			Manager::SetScene<GameScene>();
			break;
		case ENDGAME:
			Manager::SetEnd(true);
			break;
		default:
			break;
		}		

		return;
	}

	if (!FadeTitle())
	{
		player->SetController(false);
	}
	else
	{
		player->SetController(true);
	}
	
	std::vector<BillBoardObject*> billList = GetGameObjects<BillBoardObject>();
	//BillBoardObject* bill = GetGameObject<BillBoardObject>();

	SphereCollider* col = player->GetComponent<SphereCollider>();

	//��ʑJ��
	if (col->Hit(billList[0]->GetComponent<SphereCollider>()))
	{
		m_SEObj->GetComponent<Audio>()->Play();
		m_Transition->FadeOut();
		m_Select = SELECT_SCENE::GAME1;
		return;
	}

	if (col->Hit(billList[1]->GetComponent<SphereCollider>()))
	{
		m_SEObj->GetComponent<Audio>()->Play();
		m_Transition->FadeOut();	
		m_Select = SELECT_SCENE::TUTORIAL;
		return;
	}

	if (col->Hit(billList[2]->GetComponent<SphereCollider>()))
	{
		m_SEObj->GetComponent<Audio>()->Play();
		m_Transition->FadeOut();
		m_Select = SELECT_SCENE::GAME2;
		return;
	}

	if (col->Hit(billList[3]->GetComponent<SphereCollider>()))
	{
		m_SEObj->GetComponent<Audio>()->Play();
		m_Transition->FadeOut();
		m_Select = SELECT_SCENE::GAME3;
		return;
	}	

	if (col->Hit(billList[4]->GetComponent<SphereCollider>()))
	{
		m_SEObj->GetComponent<Audio>()->Play();
		m_Transition->FadeOut();
		m_Select = SELECT_SCENE::ENDGAME;
		return;
	}
}

bool TitleScene::FadeTitle()
{
	if (m_TitleMt.Diffuse.w < 0.0f)
	{
		m_TitleSprite[0]->GetComponent<Sprite>()->SetMaterial(m_TitleMt);
		m_TitleSprite[1]->GetComponent<Sprite>()->SetMaterial(m_TitleMt);		
		m_TitleSprite[2]->GetComponent<Sprite>()->SetMaterial(m_TitleMt);		
		return true;
	}

	if (m_FadeStart)
	{
		m_TitleMt.Diffuse.w -= 0.01f;

		m_TitleSprite[0]->GetComponent<Sprite>()->SetMaterial(m_TitleMt);
		m_TitleSprite[1]->GetComponent<Sprite>()->SetMaterial(m_TitleMt);
	}
	else
	{	
		//�l���グ�邩�����邩
		if (m_UpDown)
		{
			m_AnyKeyMT.Diffuse.w += 0.03f;

			if (m_AnyKeyMT.Diffuse.w > 1.0f)
			{
				m_UpDown = false;
			}
		}		
		else
		{
			m_AnyKeyMT.Diffuse.w -= 0.03f;

			if (m_AnyKeyMT.Diffuse.w < 0.0f)
			{
				m_UpDown = true;
			}
		}
	}

	if (Input::GetAnyButtonPressed())
	{
		m_FadeStart = true;
	}

	m_TitleSprite[2]->GetComponent<Sprite>()->SetMaterial(m_AnyKeyMT);

	return false;
}
