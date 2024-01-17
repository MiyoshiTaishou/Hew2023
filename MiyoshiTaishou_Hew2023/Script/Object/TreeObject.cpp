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
#include"../Component//BoxCollider.h"
#include"../Component/RigidBody.h"
#include"../Component/audio.h"

using namespace DirectX::SimpleMath;

void TreeObject::Init()
{
	this->AddComponent<ModelRenderer>()->Load("../asset\\model\\lowpoyltree.obj");
	//this->AddComponent<Shader>()->Load("../shader\\vertexLightingVS.cso", "../shader\\vertexLightingPS.cso");
	//m_Collider = this->AddComponent<BoxCollider>();
	//m_Collider->SetCollScale(Vector3(10, 100, 10));
	this->SetScale(Vector3(10, 10, 10));
	this->SetPosition(Vector3(100, -10, 0));	

	//SE
	/*m_SE = AddComponent<Audio>();
	m_SE->Load("../asset\\audio\\あっぱれ.wav");*/
}

void TreeObject::Update()
{	
	Scene* scene = Manager::GetScene();

	Player* player = scene->GetGameObject<Player>();

	if (!player)
	{
		return;
	}

	//当たったら弾き飛ばす
	//if (this->m_Collider->HitSphere(player->GetComponent<SphereCollider>()))
	//{		
	//	// 移動方向を計算する
	//	Vector3 collisionDirection = m_Position - player->GetPosition();		

	//	Vector3 playerPos = player->GetPosition();

	//	//どちらの方向から当たっているか判断する
	//	if (std::abs(collisionDirection.x) > std::abs(collisionDirection.z))
	//	{			
	//		if (collisionDirection.x > 0)
	//		{
	//			playerPos.x = m_Collider->GetPos().x - m_Collider->GetCollScale().x / 1.4;
	//		}
	//		else if (collisionDirection.x < 0)
	//		{
	//			playerPos.x = m_Collider->GetPos().x + m_Collider->GetCollScale().x / 1.4;
	//		}
	//	}
	//	else
	//	{
	//		if (collisionDirection.z > 0)
	//		{
	//			playerPos.z = m_Collider->GetPos().z - m_Collider->GetCollScale().z / 1.4;
	//		}
	//		else if (collisionDirection.z < 0)
	//		{
	//			playerPos.z = m_Collider->GetPos().z + m_Collider->GetCollScale().z / 1.4;
	//		}
	//	}

	//	player->SetPosition(playerPos);
	//	player->GetComponent<RigidBody>()->SetVelocity(Vector3::Zero);
	//}
}