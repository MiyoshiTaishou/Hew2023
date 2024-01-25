#include "StickObject.h"

#include"../Sysytem/manager.h"

#include"../Scene/scene.h"

//�R���|�[�l���g
#include"../Component/BoxCollider.h"
#include"../Component/RigidBody.h"
#include"../Component/SphereCollider.h"
#include"../Component/audio.h"
#include"../Component/shadow.h"

//�I�u�W�F�N�g
#include"field.h"
#include"camera.h"
#include"BoxObject.h"
#include"Player.h"

using namespace DirectX::SimpleMath;

void StickObject::Init()
{
	m_HitSE = AddComponent<Audio>();
	m_HitSE->Load("../asset\\audio\\�Ղ��_2.wav");

	Shadow* shadow = AddComponent<Shadow>();
	shadow->Init();
	shadow->SetSize(10.0f);
}

void StickObject::Update()
{			
	Scene* scene = Manager::GetScene();	

	Field* filed = scene->GetGameObject<Field>();

	if (!filed)
	{
		return;
	}	

	//�@�͈̓`�F�b�N 
	Vector3 max = filed->GetMax();
	Vector3 min = filed->GetMin();

	if (m_Position.x <= min.x) {
		m_Position.x = min.x;
	}
	if (m_Position.x >= max.x) {
		m_Position.x = max.x;
	}

	if (m_Position.z <= min.z) {
		m_Position.z = min.z;
	}
	if (m_Position.z >= max.z) {
		m_Position.z = max.z;
	}

	//�������Ă�����e�I�u�W�F�N�g���グ��
	if (m_Stick)
	{		
		GetComponent<Shadow>()->SetShadowView(false);		
		return;
	}
	else
	{
		float Height = filed->GetFieldHeightBySqno(m_Position, *this);

		m_Position.y = Height + 2.0f;
	}	
}

//���������Ƃ��̌Ăԏ���
void StickObject::Stick(Vector3 _pos)
{
	// ���݃V�[�����擾
	Scene* scene = Manager::GetScene();

	////�J�����擾
	//Camera* cameraObj = scene->GetGameObject<Camera>();

	m_Stick = true;
	m_Scale *= m_ScaleDown;	

	//���W�ݒ�
	//m_Position = cameraObj->GetForward() * m_Scale * 0.2f;

	//�����e���\���𑫂�
	Player* player = scene->GetGameObject<Player>();	

	// �e�I�u�W�F�N�g�̃��[�J�����W�n�ɂ�����I�t�Z�b�g�����߂�
	  // �}�g���N�X�ݒ�
	DirectX::SimpleMath::Matrix world, scale, rot, trans;
	scale = DirectX::SimpleMath::Matrix::CreateScale(player->GetScale().x, player->GetScale().y, player->GetScale().z);
	//rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(player->GetRotation().y, player->GetRotation().x, player->GetRotation().z);
	//rot = DirectX::SimpleMath::Matrix::CreateFromQuaternion(player->GetQtr());
	rot = player->m_Rotmatrix;
	trans = DirectX::SimpleMath::Matrix::CreateTranslation(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
	world = scale * rot * trans;

	// �e�I�u�W�F�N�g�iPlayer�Ȃǁj�̋t�s����擾���ă��[�J�����W�n�ɕϊ�����
	DirectX::SimpleMath::Matrix parentWorldMatrixInverse = world.Invert();
	DirectX::SimpleMath::Vector3 hitPositionLocal = DirectX::SimpleMath::Vector3::Transform(_pos, parentWorldMatrixInverse);

	// �q�I�u�W�F�N�g�̈ʒu���v�Z���ꂽ���E���W�n�̃I�t�Z�b�g�ɐݒ�
	m_Position = hitPositionLocal;

	RigidBody* body = player->GetComponent<RigidBody>();
	body->AddInetiaTensorOfSpherAngular(body->GetInetiaTensor() / 100);
	body->SetMass((body->GetMass() + 0.005f));	

	m_HitSE->Play();
}
