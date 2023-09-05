#include "Enemy.h"
#include"BoxCollider.h"
#include"modelRenderer.h"
#include"shader.h"
#include<SimpleMath.h>

using namespace DirectX::SimpleMath;

void Enemy::Init()
{
	this->AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");
	this->AddComponent<ModelRenderer>()->Load("asset\\model\\enemy.obj");
	this->SetPosition(Vector3(11.0f, 1.0f, 20.0f));
	this->AddComponent<BoxCollider>()->Init();
}

void Enemy::Update()
{
	//‰ñ“]‚³‚¹‚Ä‚¢‚é
	this->m_Rotation.y += 0.1f;

	if (m_Rotation.y > 180)
		m_Rotation.y = 0.0f;

	GameObject::Update();
}
