#include "Human.h"
#include "shader.h"
#include"shadow.h"
#include"dx11mathutil.h"
#include"ImGuiManager.h"

using namespace DirectX::SimpleMath;

void Human::Init()
{
	//AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");
	//AddComponent<Shader>()->Load("shader\\VS_LightingOneSkin.cso", "shader\\vertexLightingPS.cso"); //20230909-02

	// 使用するシェーダーを生成
	g_shader.SetShader("shader/vertexLightingVS.hlsl", "shader/vertexLightingPS.hlsl");
	//g_shader.SetShader("shader\\VS_Shadow.cso", "shader\\PS_Shadow.cso");
	//g_shader.SetShader("shader/VS_Shadow.hlsl", "shader/PS_DepthWrite.hlsl");

	
	// メッシュ生成（ジオメトリデータ）
	g_staticmesh.Init("asset\\model\\Capoeira.fbx");

	// 描画生成
	g_staticmeshrenderer.Init(g_staticmesh);

	////アニメーションロードする
	//m_Model = AddComponent<AnimationModel>();

	//m_Model->Load("asset\\model\\Capoeira.fbx");									// animation ok
	//m_Model->LoadAnimation("asset\\model\\Rumba Dancing.fbx", "Idle");
	//m_Model->LoadAnimation("asset\\model\\Capoeira.fbx", "Run");

	//影
	AddComponent<Shadow>()->SetSize(1.5f);

	m_Scale = Vector3(0.02f, 0.02f, 0.02f);
}

void Human::Uninit()
{
	g_staticmeshrenderer.Uninit();
}

void Human::Update()
{
	//毎フレームアニメーション更新
	m_Frame++;
}

void Human::Draw()
{
	//Renderer::ChangeRenderTarget();

	// デバイスコンテキスト取得
	ID3D11DeviceContext* devicecontext;
	devicecontext = Renderer::GetDeviceContext();

	// ワールド変換行列生成
	Matrix mtx;
	DX11MakeWorldMatrix(
		mtx,
		m_Scale,							// スケール
		m_Rotation,							// 姿勢
		m_Position);						// 位置

	// GPUに行列をセットする
	Renderer::SetWorldMatrix(&mtx);

	// シェーダーをGPUにセット
	g_shader.SetGPU();

	// モデル描画
	g_staticmeshrenderer.Draw();

	ImGui::Begin("AnimationModel");
	// スライダー
	ImGui::SliderFloat("Blend", &m_BlendRate, 0.0f, 1.0f);
	ImGui::End();

	//Renderer::Begin();
}

void Human::PreDraw()
{
	//m_Model->Update("Idle", m_Frame, "Run", m_Frame, m_BlendRate);
}
