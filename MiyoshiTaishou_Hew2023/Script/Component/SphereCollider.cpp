#include "SphereCollider.h"

using namespace DirectX::SimpleMath;

bool SphereCollider::Hit(const SphereCollider* _sphereCol)
{
    // 2�̋��̒��S���W�̍����v�Z
    Vector3 centerDifference;
    centerDifference.x = m_ColliderPos.x - _sphereCol->m_ColliderPos.x;
    centerDifference.y = m_ColliderPos.y - _sphereCol->m_ColliderPos.y;
    centerDifference.z = m_ColliderPos.z - _sphereCol->m_ColliderPos.z;

    // 2�̋��̒��S���W�̋�����2����v�Z
    float distanceSquared = centerDifference.x * centerDifference.x +
        centerDifference.y * centerDifference.y +
        centerDifference.z * centerDifference.z;

    // 2�̋��̔��a�̍��v���v�Z
    float radiiSum = m_Radius + _sphereCol->m_Radius;

    // �Փ˔���
    return distanceSquared <= (radiiSum * radiiSum);
}

void SphereCollider::SetRadius(float _radius)
{   
	m_Radius = _radius;
}
