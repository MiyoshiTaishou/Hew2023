#include "TakoyakiObject.h"

//�R���|�[�l���g
#include"../Component/shader.h"
#include"../Component/SphereCollider.h"

//�����_��
#include"../Render/modelRenderer.h"

using namespace DirectX::SimpleMath;

void TakoyakiObject::Init()
{
	m_Scale = Vector3(10.0f, 10.0f, 10.f);

	m_Shader = AddComponent<Shader>();
	m_Shader->Load("../shader\\VS_Object.cso", "../shader\\PS_Toon.cso");

	//AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso", "../shader\\unlitTexturePS.cso");
	//m_OutLineShader->Load("../shader\\VS_OutLine.cso", "../shader\\PS_OutLine.cso");

	ModelRenderer* model = AddComponent<ModelRenderer>();
	model->Load("../asset\\model\\bullet.obj");	

	SphereCollider* sphere = AddComponent<SphereCollider>();	
	sphere->SetRadius((ModelRenderer::Max.x * m_Scale.x));

	m_Position.x = 10.0f;

	StickObject::Init();
}

void TakoyakiObject::Draw()
{
	////�֊s���\��
	////�J�����O�o�b�N�ɕύX
	//Renderer::GetDeviceContext()->RSSetState(Renderer::m_RasterizerState[2]);
	//m_OutLineShader->Draw();
	//GetComponent<ModelRenderer>()->Draw();
	////�߂�
	//Renderer::GetDeviceContext()->RSSetState(Renderer::m_RasterizerState[1]);
}
