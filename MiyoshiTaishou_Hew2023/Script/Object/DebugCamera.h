#pragma once
#include "gameObject.h"

/**
 * @brief �v���C���[�̑���Ŏ��_���ړ��ł���J�����̃N���X�ł��B
 */
class DebugCamera : public GameObject
{
private:
    DirectX::SimpleMath::Vector3 m_Target{}; ///< �J�����̃^�[�Q�b�g���W
    DirectX::SimpleMath::Matrix m_ViewMatrix{}; ///< �J�����̃r���[�s��
    DirectX::SimpleMath::Vector3 m_Foward{}; ///< �J�����̑O���x�N�g��

public:
    /**
     * @brief DebugCamera�N���X�̏��������s���܂��B
     */
    void Init();

    /**
     * @brief DebugCamera�N���X�̍X�V�������s���܂��B
     */
    void Update();

    /**
     * @brief DebugCamera�N���X�̕`�揈�����s���܂��B
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
};
