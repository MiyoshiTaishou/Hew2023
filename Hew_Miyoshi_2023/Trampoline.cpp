#include "Trampoline.h"
#include "shader.h"
#include "modelRenderer.h"
#include "AddForce.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

/**
 * @brief Trampoline �N���X�̏������֐�
 */
void Trampoline::Init()
{
    // �V�F�[�_�[��ǂݍ���
    AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\PS_RGBSplit.cso");

    // ���f����ǂݍ���
    AddComponent<ModelRenderer>()->Load("asset\\model\\box.obj");
}

/**
 * @brief ���˂�͂�ݒ肷��
 * @param _power ���˂��
 */
void Trampoline::SetPower(float _power)
{
    power = _power;
}

/**
 * @brief �I�u�W�F�N�g�𒵂˂�����
 * @param obj ���˂�����Ώۂ� GameObject
 */
void Trampoline::Action(GameObject* obj)
{
    Vector3 vec = obj->GetComponent<Rigidbody>()->GetVelocity();

    vec.y = power;

    obj->GetComponent<Rigidbody>()->AddForce(vec, ForceMode::Impuluse);
}
