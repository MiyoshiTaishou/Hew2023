#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "DebugCamera.h"
#include "Player.h"
#include "ImGuiManager.h"

using namespace DirectX::SimpleMath;

/**
 * @brief �f�o�b�O�p�J�����̏�����
 *
 * �f�o�b�O�p�J�����̏����ʒu�ƃ^�[�Q�b�g�ʒu��ݒ肵�A�������������s���܂��B
 */
void DebugCamera::Init()
{
    m_Position = Vector3(0.0f, 10.0f, -50.0f);
    m_Target = Vector3(0.0f, 0.0f, 0.0f);
}

/**
 * @brief �f�o�b�O�p�J�����̏I������
 *
 * �f�o�b�O�p�J�����̏I���������s���܂��B
 */
void DebugCamera::Uninit()
{
}

/**
 * @brief �f�o�b�O�p�J�����̍X�V
 *
 * �f�o�b�O�p�J�����̈ʒu���X�V���܂��B
 */
void DebugCamera::Update()
{
    m_Forward = this->GetForward();
}

/**
 * @brief �f�o�b�O�p�J�����̕`��
 *
 * �f�o�b�O�p�J�����̈ʒu�Ɖ�]��ImGui���g�p���Ē������A�r���[�s��ƃv���W�F�N�V�����s���ݒ肵�܂��B
 */
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
    m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up);

    // �v���W�F�N�V�����s��̐���
    constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);
    float aspectRatio = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT);
    float nearPlane = 1.0f;
    float farPlane = 1000.0f;
    Matrix projectionMatrix;
    projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);

    Renderer::SetViewMatrix(&m_ViewMatrix);
    Renderer::SetProjectionMatrix(&projectionMatrix);
}

/**
 * @brief �J�����̃^�[�Q�b�g�ʒu��ݒ肷��
 *
 * @param target �V�����J�����̃^�[�Q�b�g�ʒu
 */
void DebugCamera::SetTarget(DirectX::SimpleMath::Vector3 target)
{
    m_Position = target;
}
