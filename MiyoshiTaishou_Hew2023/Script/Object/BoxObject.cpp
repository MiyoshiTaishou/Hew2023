#include "BoxObject.h"
#include"../Component/shader.h"
#include"../Component/BoxCollider.h"
#include"../Render/modelRenderer.h"

using namespace DirectX::SimpleMath;

void BoxObject::Init()
{
	//AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\vertexLightingPS.cso");
	AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\PS_RGBSplit.cso");
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
