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

#define MAX_FILED 20

void FakeTakoyakiObject::Init()
{
	TakoyakiObject::Init();

	RigidBody* body = AddComponent<RigidBody>();
	body->SetGravity(false);
	body->SetFreeze(FrizeNum::XRot, true);
	body->SetFreeze(FrizeNum::ZRot, true);
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

	Field* filed = scene->GetGameObject<Field>();

	//�@�͈̓`�F�b�N 
	Vector3 max = filed->GetMax();
	Vector3 min = filed->GetMin();

	if (m_Position.x <= min.x + MAX_FILED) {
		m_Position.x = min.x + MAX_FILED;
	}
	if (m_Position.x >= max.x - MAX_FILED) {
		m_Position.x = max.x - MAX_FILED;
	}

	if (m_Position.z <= min.z + MAX_FILED) {
		m_Position.z = min.z + MAX_FILED;
	}
	if (m_Position.z >= max.z - MAX_FILED) {
		m_Position.z = max.z - MAX_FILED;
	}

	m_Position.y = filed->GetFieldHeightBySqno(m_Position, *this);
	m_Position.y += 2.0f;

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
}
