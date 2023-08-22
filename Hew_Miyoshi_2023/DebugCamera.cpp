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
	// �r���[�ϊ����쐬
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up);										// ����n�ɂ����@20230511 by suzuki.tomoki

	// DIRECTXTK�̃��\�b�h�͉E��n�@20230511 by suzuki.tomoki
	// �E��n�ɂ���ƂR�p�`���_�������v���ɂȂ�̂ŕ`�悳��Ȃ��Ȃ�̂Œ���
	// ���̃R�[�h�͊m�F�e�X�g�̂��߂Ɏc��
	//	m_ViewMatrix = m_ViewMatrix.CreateLookAt(m_Position, m_Target, up);					

	Renderer::SetViewMatrix(&m_ViewMatrix);

	//�v���W�F�N�V�����s��̐���
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);    // ����p

	float aspectRatio = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT);	// �A�X�y�N�g��	
	float nearPlane = 1.0f;       // �j�A�N���b�v
	float farPlane = 1000.0f;      // �t�@�[�N���b�v

	//�v���W�F�N�V�����s��̐���
	Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);	// ����n�ɂ����@20230511 by suzuki.tomoki

	// DIRECTXTK�̃��\�b�h�͉E��n�@20230511 by suzuki.tomoki
	// �E��n�ɂ���ƂR�p�`���_�������v���ɂȂ�̂ŕ`�悳��Ȃ��Ȃ�̂Œ���
	// ���̃R�[�h�͊m�F�e�X�g�̂��߂Ɏc��
//	projectionMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}

void DebugCamera::SetTarget(DirectX::SimpleMath::Vector3 target)
{
	m_Position = target;
}