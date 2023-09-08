#pragma once
#include "scene.h"

/**
 * @brief ���U���g�V�[�� Result �N���X
 */
class Result : public Scene
{
private:
    class Transition* m_Transition{}; /**< ��ʑJ�ڂ��Ǘ�����I�u�W�F�N�g */
    class FadeUI* m_Fade{}; /**< �t�F�[�hUI���Ǘ�����I�u�W�F�N�g */

    bool m_Goal = false; /**< �V�[���J�ڃt���O */

public:
  
    void Init() override;
    void Update() override;
};
