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

	// �ɂ₩�J��������
	// 1�t���[���O�̃J�����ʒu�ۑ��ϐ�
	static Vector3 lastCamEye;
	float blendFactor = 0.5; // ���ω��̏d��
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