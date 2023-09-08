#pragma once
#include "scene.h"

/**
 * @brief �^�C�g���V�[���N���X
 */
class Title : public Scene
{
private:
    // �t�F�[�h
    class Transition* m_Transition{};
    class FadeUI* m_Fade{};

    // �V�[���J�ڃt���O
    bool m_Goal = false;

public:
  
    void Init() override;
    void Update() override;
};
