#include "SphereCollider.h"

using namespace DirectX::SimpleMath;

bool SphereCollider::Hit(const SphereCollider* _sphereCol)
{
    // 2つの球の中心座標の差を計算
    Vector3 centerDifference;
    centerDifference.x = m_ColliderPos.x - _sphereCol->m_ColliderPos.x;
    centerDifference.y = m_ColliderPos.y - _sphereCol->m_ColliderPos.y;
    centerDifference.z = m_ColliderPos.z - _sphereCol->m_ColliderPos.z;

    // 2つの球の中心座標の距離の2乗を計算
    float distanceSquared = centerDifference.x * centerDifference.x +
        centerDifference.y * centerDifference.y +
        centerDifference.z * centerDifference.z;

    // 2つの球の半径の合計を計算
    float radiiSum = m_Radius + _sphereCol->m_Radius;

    // 衝突判定
    return distanceSquared <= (radiiSum * radiiSum);
}

void SphereCollider::SetRadius(float _radius)
{   
	m_Radius = _radius;
}
