#include "Enemy.h"
#include "BoxCollider.h"
#include "ModelRenderer.h"
#include "Shader.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

/**
 * @brief 敵の初期化
 *
 * 敵の初期化処理を行います。シェーダー、モデル、位置、ボックスコライダーを設定します。
 */
void Enemy::Init()
{
    // シェーダーのロード
    this->AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");

    // モデルのロード
    this->AddComponent<ModelRenderer>()->Load("asset\\model\\enemy.obj");

    // 位置の設定
    this->SetPosition(Vector3(11.0f, 1.0f, 20.0f));

    // ボックスコライダーの初期化
    this->AddComponent<BoxCollider>()->Init();
}

/**
 * @brief 敵の更新
 *
 * 敵の状態を更新する処理を行います。回転を制御しています。
 */
void Enemy::Update()
{
    // 回転の更新
    this->m_Rotation.y += 0.1f;

    if (m_Rotation.y > 180)
        m_Rotation.y = 0.0f;

    GameObject::Update(); // 基底クラスの更新処理を呼び出す
}
