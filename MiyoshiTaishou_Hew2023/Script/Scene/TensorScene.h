#pragma once
#include"scene.h"

//審査会用回転テンソル披露シーン

class BoxObject;

class TensorScene : public Scene
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
    BoxObject* box;

    DirectX::SimpleMath::Vector3 Torque;
    DirectX::SimpleMath::Vector3 scale = { 1,1,1 };
};