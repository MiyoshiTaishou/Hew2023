#include "StickObject.h"

#include"../Sysytem/manager.h"

#include"../Scene/scene.h"

#include"../Component/BoxCollider.h"

#include"field.h"
#include"camera.h"
#include"BoxObject.h"

using namespace DirectX::SimpleMath;

void StickObject::Update()
{	
	//�������Ă����珈�������Ȃ�
	if (m_Stick)
	{				
		return;
	}
	
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

	float Height = filed->GetFieldHeightBySqno(m_Position);

	m_Position.y = Height;
}

//���������Ƃ��̌Ăԏ���
void StickObject::Stick()
{
	// ���݃V�[�����擾
	Scene* scene = Manager::GetScene();

	//�J�����擾
	Camera* cameraObj = scene->GetGameObject<Camera>();

	m_Stick = true;
	m_Scale *= m_ScaleDown;

	//���W�ݒ�
	m_Position = cameraObj->GetForward() * m_Scale * 0.2f;
}
