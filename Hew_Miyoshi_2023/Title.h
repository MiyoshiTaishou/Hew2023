#pragma once
#include "scene.h"
class Title : public Scene
{
private:
    class Transition* m_Transition{};
    class FadeUI* m_Fade{};

    //�V�[���J�ڃt���O
    bool m_Goal = false;

public:
    void Init()override;
    void Update()override;    
};

