#include "Trampoline.h"
#include"shader.h"
#include"modelRenderer.h"
#include"AddForce.h"
#include<SimpleMath.h>

using namespace DirectX::SimpleMath;

void Trampoline::Init()
{
	AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\PS_RGBSplit.cso");
	AddComponent<ModelRenderer>()->Load("asset\\model\\box.obj");
}

void Trampoline::Update()
{
}

void Trampoline::SetPower(float _power)
{
	power = _power;
}

void Trampoline::Action(GameObject* obj)
{	
	Vector3 vec = obj->GetComponent<Rigidbody>()->GetVelocity();

	//���x��y������0�ɂ���
	//obj->GetComponent<Rigidbody>()->SetVelocity({ 0,0,0 });

	vec.y = power;
	//vec.x *= -2;
	//vec.z *= -2;

	obj->GetComponent<Rigidbody>()->AddForce(vec, ForceMode::Impulse);
}
