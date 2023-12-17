#include "TitleScene.h"

//システム
#include"../Sysytem/input.h"
#include"../Sysytem/manager.h"

//オブジェクト
#include"../Object/sky.h"
#include"../Object/Player.h"
#include"../Object/field.h"
#include"../Object/camera.h"
#include"../Object/BillBoardObject.h"
#include"../Object/Yatai.h"
#include"Transition.h"

//コンポーネント
#include"../Component/shader.h"
#include"../Component/sprite.h"
#include"../Component/audio.h"
#include"../Component/SphereCollider.h"
#include"../Component/RootChaise.h"

//シーン
#include"GameScene.h"

using namespace DirectX::SimpleMath;

void TitleScene::Init()
{
	//オブジェクト生成
	AddGameObject<Sky>(Layer1);	
	Field* filed = AddGameObject<Field>(Layer1);	

	BoxObject* box = AddGameObject<BoxObject>(Layer1);
	BoxObject* box2 = AddGameObject<BoxObject>(Layer1);
	BoxObject* box3 = AddGameObject<BoxObject>(Layer1);
	BoxObject* box4 = AddGameObject<BoxObject>(Layer1);

	AddGameObject<Yatai>(Layer1);
	
	
	//　範囲チェック 
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
	m_Transition->FadeIn();//フェードイン開始	

	GameObject* titleLogo = AddGameObject<GameObject>(Layer3);// 3はレイヤ番号
	titleLogo->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\PS_BloomBlur.cso");
	titleLogo->AddComponent<Sprite>()->Init(320.0f, 0.0f, 640, 320.0f,
		"../asset\\texture\\takoyaki.png");	

	GameObject* Niji = AddGameObject<GameObject>(Layer3);// 3はレイヤ番号		
	Niji->AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso",
		"../shader\\PS_AlphaFade.cso");
	Niji->AddComponent<Sprite>()->Init(0.0f, 0.0f, 1280, 720.0f,
		"../asset\\texture\\Niji.jpg");

	BillBoardObject* bill = AddGameObject<BillBoardObject>(Layer1);
	bill->AddComponent<SphereCollider>()->SetRadius(2.0f);	

	//虹をフェードさせる
	// 毎フレームごとの時間を更新	

	
	ZeroMemory(&timeBufferDesc, sizeof(timeBufferDesc));

	timeBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	timeBufferDesc.ByteWidth = sizeof(float) * 4; // 時間データのサイズ（4つのfloat）
	timeBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	timeBufferDesc.CPUAccessFlags = 0;
	timeBufferDesc.MiscFlags = 0;
	
	ZeroMemory(&timeBufferData, sizeof(timeBufferData));
	float timeData[4] = { currentTime, 0.0f, 0.0f, 0.0f }; // 時間データを格納する場合
	timeBufferData.pSysMem = timeData;

	// 定数バッファを作成
	Renderer::GetDevice()->CreateBuffer(&timeBufferDesc, &timeBufferData, &timeBuffer);

	// シェーダーに時間データを送信
	ID3D11Buffer* timeBuffers[] = { timeBuffer };
	Renderer::GetDeviceContext()->VSSetConstantBuffers(10, 1, timeBuffers); // 頂点シェーダーに渡す場合
	Renderer::GetDeviceContext()->PSSetConstantBuffers(10, 1, timeBuffers); // ピクセルシェーダーに渡す場合
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

	//画面遷移が終了しているか
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
	float timeData[4] = { currentTime, 0.0f, 0.0f, 0.0f }; // 時間データを格納する場合
	timeBufferData.pSysMem = timeData;

	// 定数バッファを作成
	Renderer::GetDevice()->CreateBuffer(&timeBufferDesc, &timeBufferData, &timeBuffer);

	// シェーダーに時間データを送信
	ID3D11Buffer* timeBuffers[] = { timeBuffer };
	Renderer::GetDeviceContext()->VSSetConstantBuffers(10, 1, timeBuffers); // 頂点シェーダーに渡す場合
	Renderer::GetDeviceContext()->PSSetConstantBuffers(10, 1, timeBuffers); // ピクセルシェーダーに渡す場合
}