#include "TakoyakiObject.h"

//コンポーネント
#include"../Component/shader.h"
#include"../Component/SphereCollider.h"

//レンダラ
#include"../Render/modelRenderer.h"

using namespace DirectX::SimpleMath;

void TakoyakiObject::Init()
{
	m_Scale = Vector3(10.0f, 10.0f, 10.f);

	AddComponent<Shader>()->Load("../shader\\VS_Object.cso", "../shader\\PS_Toon.cso");
	ModelRenderer* model = AddComponent<ModelRenderer>();
	model->Load("../asset\\model\\bullet.obj");	

	SphereCollider* sphere = AddComponent<SphereCollider>();
	sphere->Init();
	sphere->SetRadius((ModelRenderer::Max.x * m_Scale.x));

	m_Position.x = 10.0f;
}
