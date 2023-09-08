#pragma once

#include "gameObject.h"
#include "renderer.h"

/**
 * @brief �w�i�I�u�W�F�N�g�v���C���[�ɂ��Ă��� Sky �N���X
 */
class Sky : public GameObject
{

private:
    Bloom bloom; /**< Bloom �G�t�F�N�g���Ǘ�����I�u�W�F�N�g */
    RotationAngle rot; /**< ��]�p�x���Ǘ�����I�u�W�F�N�g */

public:
  
    void Init() override;
    void Update() override;  
    void Draw() override;
};
