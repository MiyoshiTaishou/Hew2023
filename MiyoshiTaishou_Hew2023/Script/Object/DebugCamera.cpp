#include "../Sysytem/main.h"
#include "../Sysytem/manager.h"

#include "../Render/renderer.h"

#include"DebugCamera.h"
#include"Player.h"

#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void DebugCamera::Init()
{
	m_Position = Vector3(0.0f, 60.0f, -50.0f);
	m_Target = Vector3(0.0f, 20.0f, 0.0f);	
}

void DebugCamera::Update()
{	
	m_Foward = this->GetForward();

	m_Position = m_TargetObj->GetPosition() - m_Foward * 50.0f;
	this->m_Target = m_TargetObj->GetPosition() + m_Foward * 3.0f;

	// 緩やかカメラ処理
	// 1フレーム前のカメラ位置保存変数
	static Vector3 lastCamEye;
	float blendFactor = 0.5; // 平均化の重み
	m_Position.x = lastCamEye.x * blendFactor
		+ m_Position.x * (1.0f - blendFactor);
	m_Position.y = lastCamEye.y * blendFactor
		+ m_Position.y * (1.0f - blendFactor);
	m_Position.z = lastCamEye.z * blendFactor
		+ m_Position.z * (1.0f - blendFactor);

	lastCamEye = m_Position;

	this->m_Position.y += 30.0f;

	this->m_Rotation.y = m_TargetObj->GetRotation().y;
}

void DebugCamera::Draw()
{
	// ビュー変換後列作成
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up);										// 左手系にした　20230511 by suzuki.tomoki

	// DIRECTXTKのメソッドは右手系　20230511 by suzuki.tomoki
	// 右手系にすると３角形頂点が反時計回りになるので描画されなくなるので注意
	// このコードは確認テストのために残す
	//	m_ViewMatrix = m_ViewMatrix.CreateLookAt(m_Position, m_Target, up);					

	Renderer::SetViewMatrix(&m_ViewMatrix);

	//プロジェクション行列の生成
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);    // 視野角

	float aspectRatio = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT);	// アスペクト比	
	float nearPlane = 1.0f;       // ニアクリップ
	float farPlane = 1000.0f;      // ファークリップ

	//プロジェクション行列の生成
	Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);	// 左手系にした　20230511 by suzuki.tomoki

	// DIRECTXTKのメソッドは右手系　20230511 by suzuki.tomoki
	// 右手系にすると３角形頂点が反時計回りになるので描画されなくなるので注意
	// このコードは確認テストのために残す
//	projectionMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}

void DebugCamera::SetTarget(DirectX::SimpleMath::Vector3 target)
{
	m_Position = target;
}