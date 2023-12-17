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
#include"../Object/Yatai.h"
#include"Transition.h"

//�R���|�[�l���g
#include"../Component/shader.h"
#include"../Component/sprite.h"
#include"../Component/audio.h"
#include"../Component/SphereCollider.h"
#include"../Component/RootChaise.h"

//�V�[��
#include"GameScene.h"

using namespace DirectX::SimpleMath;

void TitleScene::Init()
{
	//�I�u�W�F�N�g����
	AddGameObject<Sky>(Layer1);	
	Field* filed = AddGameObject<Field>(Layer1);	

	BoxObject* box = AddGameObject<BoxObject>(Layer1);
	BoxObject* box2 = AddGameObject<BoxObject>(Layer1);
	BoxObject* box3 = AddGameObject<BoxObject>(Layer1);
	BoxObject* box4 = AddGameObject<BoxObject>(Layer1);

	AddGameObject<Yatai>(Layer1);
	
	
	//�@�͈̓`�F�b�N 
	Vector3 max = filed->GetMax();
	Vector3 min = filed->GetMin();

	box->SetPosition(Vector3(max.x, 0, 0));
	box->SetScale(Vector3(5, 20, 160));

	box2->SetPosition(Vector3(min.x, 0, 0));
	box2->SetScale(Vector3(5, 20, 160));

	box3->SetPosition(Vector3(0, 0, max.z));
	box3->SetScale(Vector3(160, 20, 5));

	box4->SetPosition(Vector3(0, 0, min.z));
	box4->SetScale(Vector3(160, 20, 5));	

	AddGameObject<Player>(Layer1);

	AddGameObject<Camera>(Layer0);	

	GameObject* bgm = AddGameObject<GameObject>(Layer3);
	bgm->AddComponent<Audio>()->Init();
	bgm->GetComponent<Audio>()->Load("../asset\\audio\\20220515cyouyaku.wav");
	bgm->GetComponent<Audio>()->Play();

	m_Transition = AddGameObject<Transition>(3);
	m_Transition->FadeIn();//�t�F�[�h�C���J�n	

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

	//�����t�F�[�h������
	// ���t���[�����Ƃ̎��Ԃ��X�V	

	
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
	BillBoardObject* bill = GetGameObject<BillBoardObject>();

	SphereCollider* col = player->GetComponent<SphereCollider>();

	if (col->Hit(bill->GetComponent<SphereCollider>()))
	{
		Manager::SetScene<GameScene>();		
		return;
	}

	currentTime += 0.005f;

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