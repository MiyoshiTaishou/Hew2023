#pragma once
#include"scene.h"

class BoxObject;

class TensorScene : public Scene
{
    class Transition* m_Transition{};

    //�V�[���J�ڃt���O
    bool m_Goal = false;

public:
    void Init()override;
    void Draw()override;
    void Update()override;

private:

    //�]�����I�u�W�F�N�g
    GameObject* sphere;
    BoxObject* box;

    DirectX::SimpleMath::Vector3 Torque;
    DirectX::SimpleMath::Vector3 scale = { 1,1,1 };
};