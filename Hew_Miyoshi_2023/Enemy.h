#pragma once
#include "gameObject.h"

/**
 * @brief �v���C���[�ɓ�����Ƃ������G
 *
 * ���̃N���X�̓v���C���[�ɓ�����Ƃ������G��\���܂��B
 */
class Enemy : public GameObject
{
public:
    /**
     * @brief �G�̏�����
     *
     * �G�̏������������s���܂��B
     */
    void Init() override;

    /**
     * @brief �G�̍X�V
     *
     * �G�̏�Ԃ��X�V���鏈�����s���܂��B
     */
    void Update() override;
};
