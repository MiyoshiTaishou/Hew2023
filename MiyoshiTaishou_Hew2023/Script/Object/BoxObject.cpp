#include "BoxObject.h"

//�Ǘ�
#include"../Sysytem/manager.h"

//�R���|�[�l���g
#include"../Component/shader.h"
#include"../Component/BoxCollider.h"

//�����_��
#include"../Render/modelRenderer.h"

//�V�[��
#include"../Scene/scene.h"

//�I�u�W�F�N�g
#include"field.h"

using namespace DirectX::SimpleMath;

void BoxObject::Init()
{
	//AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\vertexLightingPS.cso");
	//AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\PS_RGBSplit.cso");
	AddComponent<Shader>()->Load("../shader\\VS_Object.cso", "../shader\\PS_Toon.cso");
	ModelRenderer* model = AddComponent<ModelRenderer>();
	model->Load("../asset\\model\\box.obj");

	//�����蔻��̑傫�����I�u�W�F�N�g�ɍ��킹��
	Vector3 absModelScale;
	absModelScale.x = fabsf(ModelRenderer::Max.x) + fabsf(ModelRenderer::Min.x);
	absModelScale.y = fabsf(ModelRenderer::Max.y) + fabsf(ModelRenderer::Min.y);
	absModelScale.z = fabsf(ModelRenderer::Max.z) + fabsf(ModelRenderer::Min.z);

	BoxCollider* box = AddComponent<BoxCollider>();
	box->Init();
	box->SetColliderScale(absModelScale);
}
