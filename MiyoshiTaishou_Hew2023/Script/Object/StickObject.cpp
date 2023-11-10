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

	float Height = filed->GetFieldHeight(m_Position);

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
	m_Position = cameraObj->GetForward() * m_Scale * 2.0f;
}
