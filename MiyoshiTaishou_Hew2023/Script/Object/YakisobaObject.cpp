#include "YakisobaObject.h"

//システム
#include"../Sysytem/manager.h"
#include"../Scene/scene.h"

//オブジェクト
#include"../Object/Player.h"

//コンポーネント
#include"../Component/shader.h"
#include"../Render/modelRenderer.h"
#include"../Component/SphereCollider.h"
#include"../Component/BoxCollider.h"
#include"../Component/RigidBody.h"
#include"../Component/audio.h"

using namespace DirectX::SimpleMath;

void YakisobaObject::Init()
{
	this->AddComponent<ModelRenderer>()->Load("../asset\\model\\Yakisoba.obj");
	this->AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\vertexLightingPS.cso");
	m_Collider = this->AddComponent<BoxCollider>();
	m_Collider->SetCollScale(Vector3(10,100,10));
	this->SetScale(Vector3(2, 2, 2));
	this->SetPosition(Vector3(-100, 10, 0));

	//SE
	m_SE = AddComponent<Audio>();
	m_SE->Load("../asset\\audio\\あっぱれ.wav");
}

void YakisobaObject::Update()
{
	Scene* scene = Manager::GetScene();

	Player* player = scene->GetGameObject<Player>();

	if (!player)
	{
		return;
	}		
}
