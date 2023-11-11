#pragma once
#include "scene.h"
class TitleScene : public Scene
{
private:
    class Transition* m_Transition{}; 

    //シーン遷移フラグ
    bool m_Goal = false;

public:
    void Init()override;
    void Update()override;   
};

