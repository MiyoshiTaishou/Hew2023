#include "Collider.h"
#include"../Object/gameObject.h"

void Collider::Init()
{
	//�I�u�W�F�N�g�ɍ��킹��
	this->m_ColliderPos = this->m_GameObject->GetPosition();
	this->m_ColliderRot = this->m_GameObject->GetRotation();
}

void Collider::Update()
{
	//�I�u�W�F�N�g�ɍ��킹��
	this->m_ColliderPos = this->m_GameObject->GetPosition();
	this->m_ColliderRot = this->m_GameObject->GetRotation();
}

void Collider::SetColliderScale(DirectX::SimpleMath::Vector3 _scale)
{
	m_ColliderScale = _scale;
}
