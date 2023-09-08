#pragma once

#include "gameObject.h"

/**
 * @brief �f�o�b�O�p�J�����N���X
 *
 * ���̃N���X�̓f�o�b�O�p�̃J������\���܂��B
 */
class DebugCamera : public GameObject {
private:
    DirectX::SimpleMath::Vector3 m_Target{}; ///< �J�����̃^�[�Q�b�g�ʒu
    DirectX::SimpleMath::Matrix m_ViewMatrix{}; ///< �J�����̃r���[�s��
    DirectX::SimpleMath::Vector3 m_Forward{}; ///< �J�����̑O���x�N�g��

public:
   
    void Init();
    void Uninit();
    void Update();
    void Draw();

    /**
     * @brief �J�����̃^�[�Q�b�g�ʒu��ݒ肷��
     *
     * @param target �V�����J�����̃^�[�Q�b�g�ʒu
     */
    void SetTarget(DirectX::SimpleMath::Vector3 target);

    /**
     * @brief �J�����̃r���[�s����擾����
     *
     * @return �J�����̃r���[�s��
     */
    DirectX::SimpleMath::Matrix GetViewMatrix() {
        return m_ViewMatrix;
    }
};
