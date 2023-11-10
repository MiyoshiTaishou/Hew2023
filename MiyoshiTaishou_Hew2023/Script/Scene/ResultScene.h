#pragma once
#include"scene.h"

class ResultScene : public Scene
{
    class Transition* m_Transition{};

    //シーン遷移フラグ
    bool m_Goal = false;

public:
    void Init()override;
    void Update()override;
};