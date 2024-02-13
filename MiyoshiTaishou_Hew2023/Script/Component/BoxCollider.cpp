#include <WICTextureLoader.h>

#include "BoxCollider.h"
#include"SphereCollider.h"
#include"sprite.h"

#include"../ImGui/ImGuiManager.h"

#include"../Object/gameObject.h"

using namespace DirectX::SimpleMath;

void BoxCollider::Init()
{
	Collider::Init();

	//�����ݒ�
	m_Info.currentcenter = m_ColliderPos;
	m_Info.fLengthX = m_ColliderScale.x;
	m_Info.fLengthY = m_ColliderScale.y;
	m_Info.fLengthZ = m_ColliderScale.z;
}

void BoxCollider::Update()
{
	m_Info.currentcenter = m_ColliderPos;
	m_Info.fLengthX = m_ColliderScale.x;
	m_Info.fLengthY = m_ColliderScale.y;
	m_Info.fLengthZ = m_ColliderScale.z;

	m_ColliderPos = this->m_GameObject->GetPosition();	
}

void BoxCollider::Draw()
{	
	float P1Left = this->m_ColliderPos.x - (this->m_ColliderScale.x / 2);
	float P1Right = this->m_ColliderPos.x + (this->m_ColliderScale.x / 2);
	float P1Front = this->m_ColliderPos.z + (this->m_ColliderScale.z / 2);
	float P1Back = this->m_ColliderPos.z - (this->m_ColliderScale.z / 2);
	float P1Top = this->m_ColliderPos.y + (this->m_ColliderScale.y / 2);
	float P1Bottom = this->m_ColliderPos.y - (this->m_ColliderScale.y / 2);
}

bool BoxCollider::HitBox(const BoxCollider* _boxCol)
{
	float P1Left = this->m_ColliderPos.x - (this->m_ColliderScale.x / 2);
	float P1Right = this->m_ColliderPos.x + (this->m_ColliderScale.x / 2);
	float P1Front = this->m_ColliderPos.z + (this->m_ColliderScale.z / 2);
	float P1Back = this->m_ColliderPos.z - (this->m_ColliderScale.z / 2);
	float P1Top = this->m_ColliderPos.y + (this->m_ColliderScale.y / 2);
	float P1Bottom = this->m_ColliderPos.y - (this->m_ColliderScale.y / 2);

	float P2Left = _boxCol->m_ColliderPos.x - (_boxCol->m_ColliderScale.x / 2);
	float P2Right = _boxCol->m_ColliderPos.x + (_boxCol->m_ColliderScale.x / 2);
	float P2Front = _boxCol->m_ColliderPos.z + (_boxCol->m_ColliderScale.z / 2);
	float P2Back = _boxCol->m_ColliderPos.z - (_boxCol->m_ColliderScale.z / 2);
	float P2Top = _boxCol->m_ColliderPos.y + (_boxCol->m_ColliderScale.y / 2);
	float P2Bottom = _boxCol->m_ColliderPos.y - (_boxCol->m_ColliderScale.y / 2);

	if (P2Left > P1Right)
	{
		return false;
	}

	if (P2Right < P1Left)
	{
		return false;
	}

	if (P2Front < P1Back)
	{
		return false;
	}

	if (P2Back > P1Front)
	{
		return false;
	}

	return true;
}

bool BoxCollider::HitSphere(SphereCollider* _sphereCol)
{	

	// �{�b�N�X�̍ŏ��_�ƍő�_���v�Z����
	DirectX::SimpleMath::Vector3 boxMin = m_ColliderPos - m_ColliderScale * 0.5f;
	DirectX::SimpleMath::Vector3 boxMax = m_ColliderPos + m_ColliderScale * 0.5f;

	// �X�t�B�A�̒��S�ƃ{�b�N�X�̍ł��߂��_���v�Z����
	DirectX::SimpleMath::Vector3 closestPointInBox = _sphereCol->GetPos();
	closestPointInBox.x = std::max(boxMin.x, std::min(_sphereCol->GetPos().x, boxMax.x));
	closestPointInBox.y = std::max(boxMin.y, std::min(_sphereCol->GetPos().y, boxMax.y));
	closestPointInBox.z = std::max(boxMin.z, std::min(_sphereCol->GetPos().z, boxMax.z));

	// �X�t�B�A�ƃ{�b�N�X�̍ł��߂��_�̋������v�Z����
	float distance = DirectX::SimpleMath::Vector3::Distance(_sphereCol->GetPos(), closestPointInBox);

	// �X�t�B�A�̔��a�ƍł��߂��_�̋������r���A�Փ˔�����s��
	return distance <= _sphereCol->GetRadius();
}

bool BoxCollider::Collision(BoxCollider& _box)
{
	//������
	Vector3 vecSeparate;

	// 2�̃I�u�W�F�N�g�����񂾃x�N�g�����v�Z
	Vector3 vecDistance;
	Vector3 obbpos = _box.m_ColliderPos;

	vecDistance.x = m_Info.currentcenter.x - obbpos.x;
	vecDistance.y = m_Info.currentcenter.y - obbpos.y;
	vecDistance.z = m_Info.currentcenter.z - obbpos.z;

	bool sts;//�߂�l

	// OBB-A�����X�g
	Vector3* OBB_A_Axis[3] = {
		&m_Info.vecAxisX,
		&m_Info.vecAxisY,
		&m_Info.vecAxisZ,
	};

	// OBB-B�����X�g
	Vector3* OBB_B_Axis[3] = {
		&_box.m_Info.vecAxisX,
		&_box.m_Info.vecAxisY,
		&_box.m_Info.vecAxisZ,
	};

	// OBB-A�̂R���𕪗����ɂ��ă`�F�b�N
	for (int i = 0; i < 3; i++) {
		vecSeparate.x = OBB_A_Axis[i]->x;
		vecSeparate.y = OBB_A_Axis[i]->y;
		vecSeparate.z = OBB_A_Axis[i]->z;

		//���K��
		vecSeparate.Normalize();		

		sts = CompareLength(
			_box.m_Info,// OBB-B
			vecSeparate,// ������
			vecDistance);// �Q�̃I�u�W�F�N�g�̒��S�����ԃx�N�g��

		if (sts == false) 
		{
			return false;
		}		
	}

	// OBB-B�̂R���𕪗����ɂ��ă`�F�b�N
	for (int i = 0; i < 3; i++) {
		vecSeparate.x = OBB_B_Axis[i]->x;
		vecSeparate.y = OBB_B_Axis[i]->y;
		vecSeparate.z = OBB_B_Axis[i]->z;

		//���K��
		vecSeparate.Normalize();

		sts = CompareLength(
			_box.m_Info,			// OBB-B
			vecSeparate,		// ������
			vecDistance);		// �Q�̃I�u�W�F�N�g�����ԃx�N�g��

		if (sts == false)
		{
			return false;
		}
	}

	// �O�ς𕪗����Ƃ��Čv�Z
	for (int p1 = 0; p1 < 3; p1++)
	{
		for (int p2 = 0; p2 < 3; p2++) 
		{
			Vector3	crossseparate;// �O�σx�N�g��

			// �O�ς��v�Z����
			crossseparate = OBB_A_Axis[p1]->Cross(*OBB_B_Axis[p2]);
		
			// ���K��
			crossseparate.Normalize();		

			sts = CompareLength(				
				_box.m_Info,// OBB-B
				crossseparate,// ������
				vecDistance);

			// �Q�̃I�u�W�F�N�g�����ԃx�N�g��
			if (sts == false) 
			{
				return false;
			}
		}
	}

	return true;
}

bool BoxCollider::CompareLength(const OBBInfo& pboxB, const DirectX::SimpleMath::Vector3& pvecSeparate, const DirectX::SimpleMath::Vector3& pvecDistance)
{
	float fDistance;

	// �������Ɏˉe�������S�Ԃ����ԃx�N�g��
	fDistance = pvecDistance.Dot(pvecSeparate);

	// ���ς��v�Z
	fDistance = fabsf(fDistance);	// ��Βl

	//��������Ƀ{�b�N�XA���ˉe�����e�̒���
	float fShadowA = 0;

	//��������Ƀ{�b�N�X�a���ˉe�����e�̒���
	float fShadowB = 0;

	//�{�b�N�XA�́h�e�h���Z�o
	float fShadowAx;
	float fShadowAy;
	float fShadowAz;

	// X���𕪗����Ɏˉe
	fShadowAx = pvecSeparate.Dot(m_Info.vecAxisX);	
	fShadowAx = fabsf(fShadowAx * (m_Info.fLengthX / 2));

	// Y���𕪗����Ɏˉe
	fShadowAy = pvecSeparate.Dot(m_Info.vecAxisY);
	fShadowAy = fabsf(fShadowAy * (m_Info.fLengthY / 2));

	// Y���𕪗����Ɏˉe
	fShadowAz = pvecSeparate.Dot(m_Info.vecAxisZ);
	fShadowAz = fabsf(fShadowAz * (m_Info.fLengthZ / 2));

	fShadowA = fShadowAx + fShadowAy + fShadowAz;


	//�{�b�N�XB�́h�e�h���Z�o
	float fShadowBx;
	float fShadowBy;
	float fShadowBz;

	// X���𕪗����Ɏˉe
	fShadowBx = pvecSeparate.Dot(pboxB.vecAxisX);
	fShadowBx = fabsf(fShadowBx * (pboxB.fLengthX / 2));

	// Y���𕪗����Ɏˉe
	fShadowBy = pvecSeparate.Dot(pboxB.vecAxisY);
	fShadowBy = fabsf(fShadowBy * (pboxB.fLengthY / 2));

	// Y���𕪗����Ɏˉe
	fShadowBz = pvecSeparate.Dot(pboxB.vecAxisZ);
	fShadowBz = fabsf(fShadowBz * (pboxB.fLengthZ / 2));

	fShadowB = fShadowBx + fShadowBy + fShadowBz;


	if (fDistance > fShadowA + fShadowB) {
		return false;
	}

	return false;
}

bool BoxCollider::PointHit(const DirectX::SimpleMath::Vector3 point)
{
	return (point.x >= this->m_ColliderPos.x - this->m_ColliderScale.x / 2 && point.x <= this->m_ColliderPos.x + this->m_ColliderScale.x / 2) &&
		(point.y >= this->m_ColliderPos.y - this->m_ColliderScale.y / 2 && point.y <= this->m_ColliderPos.y + this->m_ColliderScale.y / 2) &&
		(point.z >= this->m_ColliderPos.z - this->m_ColliderScale.z / 2 && point.z <= this->m_ColliderPos.z + this->m_ColliderScale.z / 2);

	return false;
}
