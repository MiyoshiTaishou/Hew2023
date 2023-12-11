#include "../Sysytem/main.h"
#include "../Sysytem/manager.h"

#include "../Render/renderer.h"

#include "camera.h"
#include"Player.h"
#include"field.h"

#include"../ImGui/ImGuiManager.h"

#include"../Scene/scene.h"

using namespace DirectX::SimpleMath;

void Camera::Init()
{
	m_Position = Vector3(0.0f, 10.0f, -50.0f);
	m_Target = Vector3(0.0f, 0.0f, 0.0f);

	Scene* nowscene = Manager::GetScene();
	Player* playerobj = nowscene->GetGameObject<Player>();

	m_Foward = playerobj->GetForward();
}

void Camera::Update()
{
	Scene* nowscene = Manager::GetScene();
	Player* playerobj = nowscene->GetGameObject<Player>();

	//�J�����ƃv���C���[�����ԃx�N�g��
	camForward = playerobj->GetPosition() - m_Position;
	camForward.Normalize();

	// �x�N�g���̉������ł��쐬���邽�߂ɁAY����Z�������ւ��ĕ����𔽓]�����邱�Ƃ�90�x��]�����܂�
	camRight = Vector3(-camForward.z, 0.0f, camForward.x); // Y����Z�������ւ���X���𔽓]������
	camRight.Normalize();

	// �����W�n�ł̃J�����ʒu���X�V���邽�߂̃p�����[�^
	float radius = 50.0f; // �J�����̋���


	// �����W�n����f�J���g���W�n�֕ϊ����ăJ�����ʒu���v�Z
	Vector3 cameraPos;
	cameraPos.x = playerobj->GetPosition().x + radius * sin(phi) * cos(theta);
	cameraPos.y = playerobj->GetPosition().y + radius * cos(phi);
	cameraPos.z = playerobj->GetPosition().z + radius * sin(phi) * sin(theta);

	//m_Foward = this->GetForward();

	//m_Position = playerobj->GetPosition() - m_Foward * 50.0f;
	m_Position = cameraPos;
	this->m_Target = playerobj->GetPosition() /*+ m_Foward * 3.0f*/;

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

	//this->m_Rotation.y = playerobj->GetRotation().y;	

	//�������擾	
	Field* filed = nowscene->GetGameObject<Field>();
	if (!filed)
	{
		return;
	}

	//�@�͈̓`�F�b�N 
	Vector3 max = filed->GetMax();
	Vector3 min = filed->GetMin();

	if (m_Position.x <= min.x) {
		m_Position.x = min.x;
	}
	if (m_Position.x >= max.x) {
		m_Position.x = max.x;
	}

	if (m_Position.z <= min.z) {
		m_Position.z = min.z;
	}
	if (m_Position.z >= max.z) {
		m_Position.z = max.z;
	}

	float Height = filed->GetFieldHeightBySqno(m_Position,*this);
}

void Camera::Draw()
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

	ImGui::Begin("Camera");
	ImGui::Text("%f,%f,%f", camForward.x, camForward.y, camForward.z);
	ImGui::Text("%f,%f,%f", camRight.x, camRight.y, camRight.z);
	ImGui::End();
}

void Camera::SetTarget(DirectX::SimpleMath::Vector3 target)
{
	m_Position = target;
}