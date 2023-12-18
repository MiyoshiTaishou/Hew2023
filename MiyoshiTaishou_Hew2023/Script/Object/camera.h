#pragma once
#include <SimpleMath.h>
#include "gameObject.h"

/**
 * @brief �J�����I�u�W�F�N�g�R���|�[�l���g�Ő؂�ւ��\�ȃJ�����̃N���X�ł��B
 */
class Camera : public GameObject
{
private:
    DirectX::SimpleMath::Vector3 m_Target{}; ///< �J�����̃^�[�Q�b�g���W
    DirectX::SimpleMath::Matrix m_ViewMatrix{}; ///< �J�����̃r���[�s��
    DirectX::SimpleMath::Matrix m_ProjMatrix{}; ///< �J�����̃v���W�F�N�V�����s��
    DirectX::SimpleMath::Vector3 m_Foward{}; ///< �J�����̑O���x�N�g��

public:
    /**
     * @brief Camera�N���X�̏��������s���܂��B
     */
    void Init();

    /**
     * @brief Camera�N���X�̍X�V�������s���܂��B
     */
    void Update();

    /**
     * @brief Camera�N���X�̕`�揈�����s���܂��B
     */
    void Draw();

    /**
     * @brief �J�����̃^�[�Q�b�g���W��ݒ肵�܂��B
     * @param target �^�[�Q�b�g���W
     */
    void SetTarget(DirectX::SimpleMath::Vector3 target);

    /**
     * @brief �J�����̃r���[�s����擾���܂��B
     * @return �J�����̃r���[�s��
     */
    DirectX::SimpleMath::Matrix GetViewMatrix()
    {
        return m_ViewMatrix;
    }

    DirectX::SimpleMath::Matrix GetProjMatrix()
    {
        return m_ProjMatrix;
    }

    float theta = 30; // ���������̊p�x
    float phi = 30; // ���������̊p�x

    DirectX::SimpleMath::Vector3 camForward;
    DirectX::SimpleMath::Vector3 camRight;
};
