#include "main.h"
#include "manager.h"
#include "scene.h"
#include "modelRenderer.h"
#include "sky.h"
#include "camera.h"
#include "shader.h"

#include "ImGuiManager.h"

using namespace DirectX::SimpleMath;

/**
 * @brief Sky クラスの初期化関数
 */
void Sky::Init()
{
    m_Scale = Vector3(100.0f, 100.0f, 100.0f);

    // シェーダーを読み込み
    AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso", "shader\\PS_BloomBlur.cso");

    // モデルを読み込み
    AddComponent<ModelRenderer>()->Load("asset\\model\\sky.obj");

    // Bloom エフェクトの設定
    bloom.bloom = 1.0f;
    bloom.power = 5.0f;
    Renderer::SetBloom(bloom);
}

/**
 * @brief Sky クラスの更新関数
 */
void Sky::Update()
{
    Scene* scene = Manager::GetScene();
    Camera* camera = scene->GetGameObject<Camera>();

    if (camera)
    {
        Vector3 cameraPosition = camera->GetPosition();
        m_Position = cameraPosition;
    }

    rot.rotationAngle.x += 0.0005f;

    if (rot.rotationAngle.x > 90.0f)
        rot.rotationAngle.x = 0.0f;

    Renderer::SetRotationAngle(rot);
}

/**
 * @brief Sky クラスの描画関数
 */
void Sky::Draw()
{
    // ImGuiを使用してBloomエフェクトの設定を調整
    ImGui::Begin("Sky Bloom");
    ImGui::SliderFloat("power", &bloom.power, 0.0f, 5.0f);
    ImGui::SliderFloat("bloom", &bloom.bloom, 0.0f, 1.0f);
    ImGui::End();

    Renderer::SetBloom(bloom);
}
