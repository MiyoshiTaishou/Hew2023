#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "Player.h"
#include "ImGuiManager.h"

using namespace DirectX::SimpleMath;

/**
 * @brief カメラの初期化
 *
 * カメラの位置とターゲットを設定し、初期化処理を行います。
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
 * @brief カメラの終了処理
 *
 * カメラの終了処理を行います。
 */
void Camera::Uninit()
{
}

/**
 * @brief カメラの更新
 *
 * カメラの位置とビュー行列を更新します。また、緩やかなカメラ処理を適用します。
 */
void Camera::Update()
{
    Scene* nowscene = Manager::GetScene();
    Player* playerobj = nowscene->GetGameObject<Player>();

    m_Forward = this->GetForward();

    m_Position = playerobj->GetPosition() - m_Forward * 50.0f;
    this->m_Target = playerobj->GetPosition() + m_Forward * 3.0f;

    // 緩やかカメラ処理
    // 1フレーム前のカメラ位置保存変数
    static Vector3 lastCamEye;
    float blendFactor = 0.5; // 平均化の重み
    m_Position.x = lastCamEye.x * blendFactor + m_Position.x * (1.0f - blendFactor);
    m_Position.y = lastCamEye.y * blendFactor + m_Position.y * (1.0f - blendFactor);
    m_Position.z = lastCamEye.z * blendFactor + m_Position.z * (1.0f - blendFactor);

    lastCamEye = m_Position;

    this->m_Position.y += 10.0f;

    this->m_Rotation.y = playerobj->GetRotation().y;
}

/**
 * @brief カメラの描画
 *
 * カメラの描画処理を行います
 */
void Camera::Draw()
{   
    // ビュー変換後列作成
    Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
    m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up); // 左手系にした

    // プロジェクション行列の生成
    constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f); // 視野角
    float aspectRatio = static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT); // アスペクト比
    float nearPlane = 1.0f; // ニアクリップ
    float farPlane = 1000.0f; // ファークリップ

    // プロジェクション行列の生成
    Matrix projectionMatrix;
    projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane); // 左手系にした

    Renderer::SetViewMatrix(&m_ViewMatrix);
    Renderer::SetProjectionMatrix(&projectionMatrix);
}

/**
 * @brief カメラのターゲット位置を設定する
 *
 * @param target 新しいカメラのターゲット位置
 */
void Camera::SetTarget(DirectX::SimpleMath::Vector3 target)
{
    m_Position = target;
}
