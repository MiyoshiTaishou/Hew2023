#include "FakeTakotaki.h"

//�R���|�[�l���g
#include"../Component/RigidBody.h"
#include"../Component/shadow.h"

//�V�X�e��
#include"../Scene/scene.h"
#include"../Sysytem/manager.h"

//�I�u�W�F�N�g
#include"Player.h"
#include"field.h"

using namespace DirectX::SimpleMath;

void FakeTakoyakiObject::Init()
{
	TakoyakiObject::Init();

	AddComponent<RigidBody>()->SetGravity(false);
}

void FakeTakoyakiObject::Update()
{
	if (m_Stick)
	{
		GetComponent<Shadow>()->SetShadowView(false);
		return;
	}

	//���݂̃V�[�����擾
	Scene* scene = Manager::GetScene();

	//�v���C���[���擾
	Player* player = scene->GetGameObject<Player>();

	if (!player)
	{
		return;
	}

	//�v���C���[�ւ̃x�N�g���擾
	Vector3 toPlayerVec = m_Position - player->GetPosition();

	//�������v�Z
	float distance = toPlayerVec.Length();

	//�͈͓��Ȃ瓦����
	if (distance < m_EscapeLength)
	{
		//���K������
		toPlayerVec.Normalize();
		toPlayerVec.y = 0.0f;

		GetComponent<RigidBody>()->AddForce((toPlayerVec * m_Speed), ForceMode::Force);
	}
	else
	{
		return;
	}

	Field* filed = scene->GetGameObject<Field>();

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
}
