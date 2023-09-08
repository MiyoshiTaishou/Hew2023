#include "Enemy.h"
#include "BoxCollider.h"
#include "ModelRenderer.h"
#include "Shader.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

/**
 * @brief �G�̏�����
 *
 * �G�̏������������s���܂��B�V�F�[�_�[�A���f���A�ʒu�A�{�b�N�X�R���C�_�[��ݒ肵�܂��B
 */
void Enemy::Init()
{
    // �V�F�[�_�[�̃��[�h
    this->AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");

    // ���f���̃��[�h
    this->AddComponent<ModelRenderer>()->Load("asset\\model\\enemy.obj");

    // �ʒu�̐ݒ�
    this->SetPosition(Vector3(11.0f, 1.0f, 20.0f));

    // �{�b�N�X�R���C�_�[�̏�����
    this->AddComponent<BoxCollider>()->Init();
}

/**
 * @brief �G�̍X�V
 *
 * �G�̏�Ԃ��X�V���鏈�����s���܂��B��]�𐧌䂵�Ă��܂��B
 */
void Enemy::Update()
{
    // ��]�̍X�V
    this->m_Rotation.y += 0.1f;

    if (m_Rotation.y > 180)
        m_Rotation.y = 0.0f;

    GameObject::Update(); // ���N���X�̍X�V�������Ăяo��
}
