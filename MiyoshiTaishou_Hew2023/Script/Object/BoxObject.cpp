#include "BoxObject.h"

//管理
#include"../Sysytem/manager.h"

//コンポーネント
#include"../Component/shader.h"
#include"../Component/BoxCollider.h"

//レンダラ
#include"../Render/modelRenderer.h"

//シーン
#include"../Scene/scene.h"

//オブジェクト
#include"field.h"

using namespace DirectX::SimpleMath;

void BoxObject::Init()
{
	//AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\vertexLightingPS.cso");
	//AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\PS_RGBSplit.cso");
	AddComponent<Shader>()->Load("../shader\\VS_Object.cso", "../shader\\PS_Toon.cso");
	ModelRenderer* model = AddComponent<ModelRenderer>();
	model->Load("../asset\\model\\box.obj");

	//当たり判定の大きさをオブジェクトに合わせる
	Vector3 absModelScale;
	absModelScale.x = fabsf(ModelRenderer::Max.x) + fabsf(ModelRenderer::Min.x);
	absModelScale.y = fabsf(ModelRenderer::Max.y) + fabsf(ModelRenderer::Min.y);
	absModelScale.z = fabsf(ModelRenderer::Max.z) + fabsf(ModelRenderer::Min.z);

	BoxCollider* box = AddComponent<BoxCollider>();
	box->Init();
	box->SetColliderScale(absModelScale);
}
