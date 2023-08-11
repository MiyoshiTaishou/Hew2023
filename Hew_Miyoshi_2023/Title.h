#pragma once
#include "scene.h"
class Title : public Scene
{
private:
    class Transition* m_Transition{};
    class FadeUI* m_Fade{};

    //シーン遷移フラグ
    bool m_Goal = false;

public:
    void Init()override;
    void Update()override;    
};

