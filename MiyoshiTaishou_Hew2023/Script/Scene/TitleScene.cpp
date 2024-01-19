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

using namespace DirectX::SimpleMath;

void TitleScene::Init()
{
	Score* score = AddGameObject<Score>(Layer3);

	//�I�u�W�F�N�g����
	AddGameObject<Sky>(Layer1);	
	Field* filed = AddGameObject<Field>(Layer1);
	filed->Init("Title.csv");

	Player* player = AddGameObject<Player>(Layer1);
	player->SetPosition(Vector3(0, 40, -140));

	//�I�u�W�F�N�g���[�h
	LoadObjectData("titleMap.csv");	

	AddGameObject<Camera>(Layer0);	
	
	//BGM
	GameObject* bgm = AddGameObject<GameObject>(Layer3);
	bgm->AddComponent<Audio>()->Init();
	bgm->GetComponent<Audio>()->Load("../asset\\audio\\20220515cyouyaku.wav");
	bgm->GetComponent<Audio>()->Play();	

	//�^�C�g���摜
	GameObject* titleLogo = AddGameObject<GameObject>(Layer3);// 3�̓��C���ԍ�
	titleLogo->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\PS_BloomBlur.cso");
	titleLogo->AddComponent<Sprite>()->Init(320.0f, -100.0f, 640, 320.0f,
		"../asset\\texture\\takoyaki.png");	

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
		switch (m_Select)
		{
		case TUTORIAL:
			Manager::SetScene<TutorialScene>();
			break;
		case GAME1:
			Manager::SetFiledName("GameMap1-1.csv");
			Manager::SetMapName("1-1.csv");
			Manager::SetScene<GameScene>();			
			break;
		case GAME2:		
			Manager::SetFiledName("testMap.csv");
			Manager::SetMapName("Stage1-2.csv");
			Manager::SetScene<GameScene>();			
			break;
		default:
			break;
		}		

		return;
	}

	Player* player = GetGameObject<Player>();
	std::vector<BillBoardObject*> billList = GetGameObjects<BillBoardObject>();
	BillBoardObject* bill = GetGameObject<BillBoardObject>();

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
		m_Select = SELECT_SCENE::GAME2;
		return;
	}

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
}