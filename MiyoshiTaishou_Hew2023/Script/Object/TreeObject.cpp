#include "TreeObject.h"

//システム
#include"../Sysytem/manager.h"
#include"../Scene/scene.h"

//オブジェクト
#include"../Object/Player.h"

//コンポーネント
#include"../Component/shader.h"
#include"../Render/modelRenderer.h"
#include"../Component/SphereCollider.h"
#include"../Component/RigidBody.h"
#include"../Component/audio.h"

using namespace DirectX::SimpleMath;

void TreeObject::Init()
{
	this->AddComponent<ModelRenderer>()->Load("../asset\\model\\lowpoyltree.obj");
	this->AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\vertexLightingPS.cso");
	m_Collider = this->AddComponent<SphereCollider>();
	m_Collider->SetRadius(15.0f);
	this->SetScale(Vector3(10, 10, 10));
	this->SetPosition(Vector3(100, -10, 0));	

	//SE
	m_SE = AddComponent<Audio>();
	m_SE->Load("../asset\\audio\\あっぱれ.wav");
}

void TreeObject::Update()
{	
	Scene* scene = Manager::GetScene();

	Player* player = scene->GetGameObject<Player>();

	//当たったら弾き飛ばす
	if (this->m_Collider->Hit(player->GetComponent<SphereCollider>()))
	{
		RigidBody* body = player->GetComponent<RigidBody>();
		Vector3 playerVel = body->GetVelocity();

		playerVel *= -1.1;

		playerVel.y = 0.0f;

		body->AddForce(playerVel, ForceMode::Impulse);

		m_SE->Play();
	}
}