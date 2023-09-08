#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "DebugCamera.h"
#include "Player.h"
#include "ImGuiManager.h"

using namespace DirectX::SimpleMath;

/**
 * @brief デバッグ用カメラの初期化
 *
 * デバッグ用カメラの初期位置とターゲット位置を設定し、初期化処理を行います。
 */
void DebugCamera::Init()
{
    m_Position = Vector3(0.0f, 10.0f, -50.0f);
    m_Target = Vector3(0.0f, 0.0f, 0.0f);
}

/**
 * @brief デバッグ用カメラの終了処理
 *
 * デバッグ用カメラの終了処理を行います。
 */
void DebugCamera::Uninit()
{
}

/**
 * @brief デバッグ用カメラの更新
 *
 * デバッグ用カメラの位置を更新します。
 */
void DebugCamera::Update()
{
    m_Forward = this->GetForward();
}

/**
 * @brief デバッグ用カメラの描画
 *
 * デバッグ用カメラの位置と回転をImGuiを使用して調整し、ビュー行列とプロジェクション行列を設定します。
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

    // ビュー変換後列作成
    Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
    m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up);

    // プロジェクション行列の生成
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
 * @brief カメラのターゲット位置を設定する
 *
 * @param target 新しいカメラのターゲット位置
 */
void DebugCamera::SetTarget(DirectX::SimpleMath::Vector3 target)
{
    m_Position = target;
}
