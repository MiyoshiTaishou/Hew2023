#include "Goal.h"
#include"modelRenderer.h"
#include"shader.h"
//#include"BoxCollider.h"
#include<SimpleMath.h>

using namespace DirectX::SimpleMath;

void Goal::Init()
{
	this->AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");
	this->AddComponent<ModelRenderer>()->Load("asset\\model\\goal.obj");	
	this->SetPosition(Vector3(-11.0f, 10.0f, 20.0f));
	//this->AddComponent<BoxCollider>()->Init();
}
