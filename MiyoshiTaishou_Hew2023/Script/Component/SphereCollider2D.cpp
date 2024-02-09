#include "SphereCollider2D.h"
#include"../Object/gameObject.h"

using namespace DirectX::SimpleMath;

Vector3 SphereCollider2D::Hit(const SphereCollider2D* _sphereCol)
{
	//ãóó£ÇåvéZ
	float distance = std::sqrt(std::powl(m_GameObject->GetPosition().x - _sphereCol->m_GameObject->GetPosition().x, 2) 
		+ std::powl(m_GameObject->GetPosition().y - _sphereCol->m_GameObject->GetPosition().y, 2));

    //ÇﬂÇËçûÇ›âè¡
    if (distance < m_Radius + _sphereCol->m_Radius) 
    {
        double overlapDistance = (m_Radius + _sphereCol->m_Radius) - distance;
        double unitVectorX = (m_GameObject->GetPosition().x - _sphereCol->m_GameObject->GetPosition().x) / distance;
        double unitVectorY = (m_GameObject->GetPosition().y - _sphereCol->m_GameObject->GetPosition().y) / distance;

        Vector3 disPos;
        disPos.x = unitVectorX * overlapDistance;
        disPos.y = unitVectorY * overlapDistance;

        return disPos;
    }

    return Vector3::Zero;
}
