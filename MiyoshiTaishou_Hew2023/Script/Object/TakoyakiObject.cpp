#include "TakoyakiObject.h"

//コンポーネント
#include"../Component/shader.h"
#include"../Component/SphereCollider.h"

//レンダラ
#include"../Render/modelRenderer.h"

using namespace DirectX::SimpleMath;

void TakoyakiObject::Init()
{
	float size = rand() % 10 + 10;
	m_Scale = Vector3(size, size, size);

	m_Shader = AddComponent<Shader>();	
	m_Shader->Load("../shader\\VS_GouraudShading.cso", "../shader\\PS_OrangeScale.cso");

	ModelRenderer* model = AddComponent<ModelRenderer>();
	model->Load("../asset\\model\\bullet.obj");	

	SphereCollider* sphere = AddComponent<SphereCollider>();	
	sphere->SetRadius(0.2 * m_Scale.x);	

	StickObject::Init();
}