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
 * @brief Sky �N���X�̏������֐�
 */
void Sky::Init()
{
    m_Scale = Vector3(100.0f, 100.0f, 100.0f);

    // �V�F�[�_�[��ǂݍ���
    AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso", "shader\\PS_BloomBlur.cso");

    // ���f����ǂݍ���
    AddComponent<ModelRenderer>()->Load("asset\\model\\sky.obj");

    // Bloom �G�t�F�N�g�̐ݒ�
    bloom.bloom = 1.0f;
    bloom.power = 5.0f;
    Renderer::SetBloom(bloom);
}

/**
 * @brief Sky �N���X�̍X�V�֐�
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
 * @brief Sky �N���X�̕`��֐�
 */
void Sky::Draw()
{
    // ImGui���g�p����Bloom�G�t�F�N�g�̐ݒ�𒲐�
    ImGui::Begin("Sky Bloom");
    ImGui::SliderFloat("power", &bloom.power, 0.0f, 5.0f);
    ImGui::SliderFloat("bloom", &bloom.bloom, 0.0f, 1.0f);
    ImGui::End();

    Renderer::SetBloom(bloom);
}
