#pragma once
#include<SimpleMath.h>
#include "component.h"

//OBB�p�\����
struct OBBinfo
{
	DirectX::SimpleMath::Vector3 vecAxisX;//X��
	DirectX::SimpleMath::Vector3 vecAxisY;//Y��
	DirectX::SimpleMath::Vector3 vecAxisZ;//Z��
	DirectX::SimpleMath::Vector3 center;//���S���W(���[�J�����W�n)
	DirectX::SimpleMath::Vector3 currentcenter;//BBOX�̌��݈ʒu
	float fLengthX;//BBOX X�T�C�Y
	float fLengthY;//BBOX Y�T�C�Y
	float fLengthZ;//BBOX Z�T�C�Y
};

bool CompareLength(
	const OBBinfo& pboxA,
	const OBBinfo& pboxB,
	const DirectX::SimpleMath::Vector3& pvecSeparate,// ������
	const DirectX::SimpleMath::Vector3& pvecDistance)
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
	fShadowAx = pvecSeparate.Dot(pboxA.vecAxisX);	
	fShadowAx = fabsf(fShadowAx * (pboxA.fLengthX / 2));
	// Y���𕪗����Ɏˉe
	fShadowAy = pvecSeparate.Dot(pboxA.vecAxisY);
	fShadowAy = fabsf(fShadowAy * (pboxA.fLengthY / 2));
	
	// Z���𕪗����Ɏˉe
	fShadowAz = pvecSeparate.Dot(pboxA.vecAxisZ);
	fShadowAz = fabsf(fShadowAz * (pboxA.fLengthZ / 2));
	
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
	
	// Z���𕪗����Ɏˉe
	fShadowBz = pvecSeparate.Dot(pboxB.vecAxisZ);
	fShadowBz = fabsf(fShadowBz * (pboxB.fLengthZ / 2));
	
	fShadowB = fShadowBx + fShadowBy + fShadowBz;
	
	if (fDistance > fShadowA + fShadowB) {
		return false;
	}
	return true;
}

bool Collisom(OBBinfo& obbA, OBBinfo& obbB)
{
	//������
	DirectX::SimpleMath::Vector3 vecSeparate;

	// 2�̃I�u�W�F�N�g�����񂾃x�N�g�����v�Z
	DirectX::SimpleMath::Vector3 vecDistance;

	DirectX::SimpleMath::Vector3 obbposA = obbA.currentcenter;
	DirectX::SimpleMath::Vector3 obbposB = obbB.currentcenter;

	vecDistance.x = obbposA.x - obbposB.x;
	vecDistance.y = obbposA.y - obbposB.y;
	vecDistance.z = obbposA.z - obbposB.z;

	bool sts;// �߂�l

	// OBB-A�����X�g
	DirectX::SimpleMath::Vector3* OBB_A_Axis[3] = {
		&obbA.vecAxisX,
		&obbA.vecAxisY,
		&obbA.vecAxisZ,
	};

	// OBB-B�����X�g
	DirectX::SimpleMath::Vector3* OBB_B_Axis[3] = {
		&obbB.vecAxisX,
		&obbB.vecAxisY,
		&obbB.vecAxisZ,
	};

	// OBB-A�̂R���𕪗����ɂ��ă`�F�b�N
	for (int i = 0; i < 3; i++) {
		vecSeparate.x = OBB_A_Axis[i]->x;
		vecSeparate.y = OBB_A_Axis[i]->y;
		vecSeparate.z = OBB_A_Axis[i]->z;

		vecSeparate.Normalize();//���K��

		sts = CompareLength(obbA,// OBB-A
			obbA,// OBB-B
			vecSeparate,// ������
			vecDistance);// �Q�̃I�u�W�F�N�g�̒��S�����ԃx�N�g��
		if (sts == false) {
			return false;
		}
	}

	// OBB-B�̂R���𕪗����ɂ��ă`�F�b�N
	for (int i = 0; i < 3; i++) {
		vecSeparate.x = OBB_B_Axis[i]->x;
		vecSeparate.y = OBB_B_Axis[i]->y;
		vecSeparate.z = OBB_B_Axis[i]->z;

		vecSeparate.Normalize();//���K��
		sts = CompareLength(obbA,// OBB-A
			obbA,// OBB-B
			vecSeparate,// ������
			vecDistance);// �Q�̃I�u�W�F�N�g�̒��S�����ԃx�N�g��
		if (sts == false) {
			return false;
		}
	}

	// �O�ς𕪗����Ƃ��Čv�Z
	for (int p1 = 0; p1 < 3; p1++) {
		for (int p2 = 0; p2 < 3; p2++) {
			DirectX::SimpleMath::Vector3	crossseparate;// �O�σx�N�g��

			// �O�ς��v�Z����
			crossseparate = OBB_A_Axis[p1]->Cross(*OBB_B_Axis[p2]);

			// ���K��
			crossseparate.Normalize();

			sts = CompareLength(
				obbA,// OBB-A
				obbB,// OBB-B
				crossseparate,// ������
				vecDistance);
			// �Q�̃I�u�W�F�N�g�����ԃx�N�g��
			if (sts == false) {
				return false;
			}
		}
	}

	return true;
}