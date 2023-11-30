#pragma once
#include"scene.h"

class SlopeScene : public Scene
{
    class Transition* m_Transition{};

    //シーン遷移フラグ
    bool m_Goal = false;

public:
    void Init()override;
    void Draw()override;
    void Update()override;

private:

    //転がすオブジェクト
    GameObject* sphere;

    DirectX::SimpleMath::Vector3 force;
};