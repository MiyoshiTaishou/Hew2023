#include "Collider.h"
#include"../Object/gameObject.h"

using namespace DirectX::SimpleMath;

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

bool Collider::CheckInTriangle(const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b, const DirectX::SimpleMath::Vector3& c, const DirectX::SimpleMath::Vector3& p)
{
	Vector3	ab, bc, ca;			// �R�ӂ̃x�N�g��
	Vector3	ap, bp, cp;			// �����̓_�Ƃ̃x�N�g��
	Vector3	normal;				// �R�p�`�̖@���x�N�g��
	Vector3	n1, n2, n3;			// �R�ӂƓ����̓_�Ƃ̖@���x�N�g��

	ab = b - a;

	bc = c - b;

	ca = a - c;

	ap = p - a;

	bp = p - b;

	cp = p - c;

	normal = ab.Cross(bc);

	n1 = ab.Cross(ap);

	n2 = bc.Cross(bp);

	n3 = ca.Cross(cp);

	float dot = n1.Dot(normal);
	if (dot < 0) return false;			// �ׂ��p�x���݊p

	dot = n2.Dot(normal);
	if (dot < 0) return false;			// �ׂ��p�x���݊p

	dot = n3.Dot(normal);
	if (dot < 0) return false;			// �ׂ��p�x���݊p

	return true;
}

bool Collider::LinetoPlaneCross(const Plane& plane, const Vector3& p0, const Vector3& wv, float& t, Vector3& ans)
{
	Vector3 normal;				// ���ʂ̖@���x�N�g���i���K���ς݁j
	normal.x = plane.x;
	normal.y = plane.y;
	normal.z = plane.z;

	float dot;			// ����

	dot = wv.Dot(normal);
	// ���s�`�F�b�N(���ς��v�Z����)
	if (fabsf(dot) < FLT_EPSILON) {
		//		MessageBox(nullptr, "���s�ł��B", "���s�ł��B", MB_OK);

		printf("���s�ł� \n");
		return false;
	}

	// �����ɂ������߂鎮������
	float dot2;			// ���q
	dot2 = p0.Dot(normal);

	t = -(dot2 + plane.w) / dot;

	ans.x = p0.x + wv.x * t;
	ans.y = p0.y + wv.y * t;
	ans.z = p0.z + wv.z * t;
	return true;
}
