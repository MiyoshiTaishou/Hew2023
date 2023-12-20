#include "TreeObject.h"

//�V�X�e��
#include"../Sysytem/manager.h"
#include"../Scene/scene.h"

//�I�u�W�F�N�g
#include"../Object/Player.h"

//�R���|�[�l���g
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
	m_SE->Load("../asset\\audio\\�����ς�.wav");
}

void TreeObject::Update()
{	
	Scene* scene = Manager::GetScene();

	Player* player = scene->GetGameObject<Player>();

	//����������e����΂�
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