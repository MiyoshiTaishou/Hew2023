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

	LoadObjectData("titleMap.csv");

	AddGameObject<TreeObject>(Layer1);
	AddGameObject<YakisobaObject>(Layer1);
	AddGameObject<YataiObject>(Layer1);
	AddGameObject<KasuteraObject>(Layer1);
	AddGameObject<CarObject>(Layer1);	

	//�͈̓`�F�b�N 
	Vector3 max = filed->GetMax();
	Vector3 min = filed->GetMin();		

	AddGameObject<Camera>(Layer0);	
	

	GameObject* bgm = AddGameObject<GameObject>(Layer3);
	bgm->AddComponent<Audio>()->Init();
	bgm->GetComponent<Audio>()->Load("../asset\\audio\\20220515cyouyaku.wav");
	bgm->GetComponent<Audio>()->Play();	

	GameObject* titleLogo = AddGameObject<GameObject>(Layer3);// 3�̓��C���ԍ�
	titleLogo->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\PS_BloomBlur.cso");
	titleLogo->AddComponent<Sprite>()->Init(320.0f, 0.0f, 640, 320.0f,
		"../asset\\texture\\takoyaki.png");	

	GameObject* Niji = AddGameObject<GameObject>(Layer3);// 3�̓��C���ԍ�		
	Niji->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\PS_AlphaFade.cso");
	Niji->AddComponent<Sprite>()->Init(0.0f, 0.0f, 1280, 720.0f,
		"../asset\\texture\\Niji.jpg");

	BillBoardObject* bill = AddGameObject<BillBoardObject>(Layer1);
	bill->AddComponent<SphereCollider>()->SetRadius(2.0f);	
	bill->SetPosition(Vector3(100, 0, 50));

	BillBoardObject* bill2 = AddGameObject<BillBoardObject>(Layer1);	
	bill2->Init("../asset/texture/Tutorial.png");
	bill2->AddComponent<SphereCollider>()->SetRadius(2.0f);
	bill2->SetPosition(Vector3(0, 0, 50));

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
		Manager::SetScene<GameScene>();

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
		return;
	}

	if (col->Hit(billList[1]->GetComponent<SphereCollider>()))
	{
		m_SEObj->GetComponent<Audio>()->Play();
		Manager::SetScene<TutorialScene>();
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