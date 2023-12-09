#define NOMINMAX

#include"BoundingSphere.h"
#include"../Render/modelRenderer.h"

using namespace DirectX::SimpleMath;

// ���[���h���W���v�Z����i�ΏۃI�u�W�F�N�g�̍s��iRTS�j���������j
Vector3 BoundingSphere::CalcWorldPos(DirectX::SimpleMath::Matrix mtx) 
{
	return Vector3::Transform(m_center, mtx);
}

// BS���𐶐�����
void BoundingSphere::Caliculate() 
{

	std::vector<float > lengthlist;

	Vector3 max;
	Vector3 min;

	// �ő�l�ƍŏ��l�����߂�	
	m_min = ModelRenderer::Min;
	m_max = ModelRenderer::Max;
	
	// ���S�����߂�
	m_center = (max + min) * 0.5f;

	float iter = (max - m_center).Length();

	m_radius = iter;
}

// ���a��߂�
float BoundingSphere::GetRadius()
{
	return m_radius;	
}

// ���S���W��߂�
Vector3 BoundingSphere::GetCenter()
{
	return m_center;
}

// BS��񐶐�
BoundingSphere BoundingSphere::MakeBS(
	Matrix mtx,			// �I�u�W�F�N�g�̍s��iRTS���j
	Vector3 scale)			// �I�u�W�F�N�g�̃X�P�[���l
{

	BoundingSphere bs;

	// ���S���W�v�Z
	Vector3 wpos = CalcWorldPos(mtx);
	bs.m_center = wpos;

	// ���a�̍Čv�Z�i�g�k������ׁj
	float maxsclae = std::max(std::max(scale.x, scale.y), scale.z);
	bs.m_radius = m_radius * maxsclae;

	return bs;
}

// BS�`��p�̃��[���h�ϊ��s��𐶐�����
Matrix BoundingSphere::MakeWorldMtx(
	Vector3 scale,
	Matrix wmtx) 
{

	// �P���ɂR�c�W�I���g����񂩂�a�r�����쐬���Ă�
	//�i�g�k���l������Ă��Ȃ��j
	float smax;
	smax = std::max(std::max(scale.x, scale.y), scale.z);

	// �ő�̊g�嗦�ōs�񐶐�
	Matrix mtx = Matrix::CreateScale(smax, smax, smax);
	Vector3 bspos = CalcWorldPos(wmtx);

	// �o�E���f�B���O�X�t�B�A�p�̃��[���h�ϊ��s��ɂ���i���S������Ă�̂ŏC���j
	mtx._41 = bspos.x;
	mtx._42 = bspos.y;
	mtx._43 = bspos.z;

	return mtx;
}

// �ő�l�擾
Vector3 BoundingSphere::GetMax() {
	return m_max;
}

// �ŏ��l�擾
Vector3 BoundingSphere::GetMin() {
	return m_min;
}
