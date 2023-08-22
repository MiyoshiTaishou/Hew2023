#include "main.h"
#include "manager.h"
#include "renderer.h"
#include"DebugCamera.h"
#include"BackCameraComponent.h"
#include"Player.h"

#include"ImGuiManager.h"

using namespace DirectX::SimpleMath;

void DebugCamera::Init()
{
	m_Position = Vector3(0.0f, 10.0f, -50.0f);
	m_Target = Vector3(0.0f, 0.0f, 0.0f);	
}

void DebugCamera::Uninit()
{
}



void DebugCamera::Update()
{	
	m_Foward = this->GetForward();		
}

void DebugCamera::Draw()
{
	ImGui::Begin("Camera");

	ImGui::SliderFloat("posX", &this->m_Position.x, -100.0f, 100.0f);
	ImGui::SliderFloat("posY", &this->m_Position.y, -100.0f, 100.0f);
	ImGui::SliderFloat("posZ", &this->m_Position.z, -100.0f, 100.0f);

	ImGui::SliderFloat("targetX", &this->m_Target.x, -100.0f, 100.0f);
	ImGui::SliderFloat("targetY", &this->m_Target.y, -100.0f, 100.0f);
	ImGui::SliderFloat("targetZ", &this->m_Target.z, -100.0f, 100.0f);

	ImGui::SliderFloat("rotX", &this->m_Rotation.x, -100.0f, 100.0f);
	ImGui::SliderFloat("rotY", &this->m_Rotation.y, -100.0f, 100.0f);
	ImGui::SliderFloat("rotZ", &this->m_Rotation.z, -100.0f, 100.0f);

	ImGui::End();
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