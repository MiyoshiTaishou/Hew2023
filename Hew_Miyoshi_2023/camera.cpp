#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "Player.h"
#include "ImGuiManager.h"

using namespace DirectX::SimpleMath;

/**
 * @brief �J�����̏�����
 *
 * �J�����̈ʒu�ƃ^�[�Q�b�g��ݒ肵�A�������������s���܂��B
 */
void Camera::Init()
{
    m_Position = Vector3(0.0f, 10.0f, -50.0f);
    m_Target = Vector3(0.0f, 0.0f, 0.0f);

    Scene* nowscene = Manager::GetScene();
    Player* playerobj = nowscene->GetGameObject<Player>();
    m_Forward = playerobj->GetForward();
}

/**
 * @brief �J�����̏I������
 *
 * �J�����̏I���������s���܂��B
 */
void Camera::Uninit()
{
}

/**
 * @brief �J�����̍X�V
 *
 * �J�����̈ʒu�ƃr���[�s����X�V���܂��B�܂��A�ɂ₩�ȃJ����������K�p���܂��B
 */
void Camera::Update()
{
    Scene* nowscene = Manager::GetScene();
    Player* playerobj = nowscene->GetGameObject<Player>();

    m_Forward = this->GetForward();

    m_Position = playerobj->GetPosition() - m_Forward * 50.0f;
    this->m_Target = playerobj->GetPosition() + m_Forward * 3.0f;

    // �ɂ₩�J��������
    // 1�t���[���O�̃J�����ʒu�ۑ��ϐ�
    static Vector3 lastCamEye;
    float blendFactor = 0.5; // ���ω��̏d��
    m_Position.x = lastCamEye.x * blendFactor + m_Position.x * (1.0f - blendFactor);
    m_Position.y = lastCamEye.y * blendFactor + m_Position.y * (1.0f - blendFactor);
    m_Position.z = lastCamEye.z * blendFactor + m_Position.z * (1.0f - blendFactor);

    lastCamEye = m_Position;

    this->m_Position.y += 10.0f;

    this->m_Rotation.y = playerobj->GetRotation().y;
}

/**
 * @brief �J�����̕`��
 *
 * �J�����̕`�揈�����s���܂�
 */
void Camera::Draw()
{   
    // �r���[�ϊ����쐬
    Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
    m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up); // ����n�ɂ���

    // �v���W�F�N�V�����s��̐���
    constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f); // ����p
    float aspectRatio = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT); // �A�X�y�N�g��
    float nearPlane = 1.0f; // �j�A�N���b�v
    float farPlane = 1000.0f; // �t�@�[�N���b�v

    // �v���W�F�N�V�����s��̐���
    Matrix projectionMatrix;
    projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane); // ����n�ɂ���

    Renderer::SetViewMatrix(&m_ViewMatrix);
    Renderer::SetProjectionMatrix(&projectionMatrix);
}

/**
 * @brief �J�����̃^�[�Q�b�g�ʒu��ݒ肷��
 *
 * @param target �V�����J�����̃^�[�Q�b�g�ʒu
 */
void Camera::SetTarget(DirectX::SimpleMath::Vector3 target)
{
    m_Position = target;
}
