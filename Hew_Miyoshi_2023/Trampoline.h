#pragma once
#include "gameObject.h"

/**
 * @brief ��ɏ��ƒ��˂�I�u�W�F�N�g Trampoline �N���X
 */
class Trampoline : public GameObject
{
public:
 
    void Init() override;

    /**
     * @brief ���˂鋭����ݒ肷��
     * @param _power ���˂鋭��
     */
    void SetPower(float _power);

    /**
     * @brief �I�u�W�F�N�g�𒵂˂�����
     * @param obj ���˂�����Ώۂ� GameObject
     */
    void Action(GameObject* obj);

private:
    float power = 300.0f; /**< ���˂鋭�� */
};
