#include "SphereCollider.h"

using namespace DirectX::SimpleMath;

void SphereCollider::Init()
{
    Collider::Init();

    //������悤�ɂ��邩
    if (m_Invisble)
    {
        return;
    }

    //���̃��b�V���ǉ�  
    m_Sphere = new CSphereMesh();
    m_Sphere->Init(2.0f, Color(1, 1, 1, 1), 100, 100);  

    m_MeshRenderer = new CMeshRenderer();
    m_MeshRenderer->Init(*m_Sphere);

    m_SphereMt.Ambient = Color(0, 0, 0, 0);
    m_SphereMt.Diffuse = Color(1, 1, 1, 0.3f);
    m_SphereMt.Specular = Color(0, 0, 0, 0);
    m_SphereMt.Shininess = 0;
    m_SphereMt.Emission = Color(0, 0, 0, 0);
    m_SphereMt.TextureEnable = FALSE;
}

void SphereCollider::Uninit()
{
    if (m_Invisble)
    {
        return;
    }

    delete m_Sphere;
    m_Sphere = nullptr;

    delete m_MeshRenderer;
    m_MeshRenderer = nullptr;
}

void SphereCollider::Draw()
{
    if (m_Invisble)
    {
        return;
    }

    // ���[���h�ϊ��s�񐶐�
    // �}�g���N�X�ݒ�
    Matrix world, scale, trans;
    scale = DirectX::SimpleMath::Matrix::CreateScale(Vector3(1.0f, 1.0f, 1.0f));
    trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_ColliderPos.x, m_ColliderPos.y, m_ColliderPos.z);
    world = scale * trans;
    // GPU�ɍs����Z�b�g����
    Renderer::SetWorldMatrix(&world);//�ʒu

    // �}�e���A���ݒ�
    Renderer::SetMaterial(m_SphereMt);

    m_MeshRenderer->Draw();
}

bool SphereCollider::Hit(const SphereCollider* _sphereCol)
{
    //�L����
    if (!m_CanHit || !_sphereCol->m_CanHit)
    {
        return false;
    }

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

float SphereCollider::GetRadius()
{
    return m_Radius;
}
