#include "Trampoline.h"
#include "shader.h"
#include "modelRenderer.h"
#include "AddForce.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

/**
 * @brief Trampoline クラスの初期化関数
 */
void Trampoline::Init()
{
    // シェーダーを読み込み
    AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\PS_RGBSplit.cso");

    // モデルを読み込み
    AddComponent<ModelRenderer>()->Load("asset\\model\\box.obj");
}

/**
 * @brief 跳ねる力を設定する
 * @param _power 跳ねる力
 */
void Trampoline::SetPower(float _power)
{
    power = _power;
}

/**
 * @brief オブジェクトを跳ねさせる
 * @param obj 跳ねさせる対象の GameObject
 */
void Trampoline::Action(GameObject* obj)
{
    Vector3 vec = obj->GetComponent<Rigidbody>()->GetVelocity();

    vec.y = power;

    obj->GetComponent<Rigidbody>()->AddForce(vec, ForceMode::Impuluse);
}
