#pragma once
#include"scene.h"

class ResultScene : public Scene
{
    class Transition* m_Transition{};

    //�V�[���J�ڃt���O
    bool m_Goal = false;

public:
    void Init()override;
    void Update()override;
};