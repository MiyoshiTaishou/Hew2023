#pragma once
#include"scene.h"

class SlopeScene : public Scene
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

    DirectX::SimpleMath::Vector3 force;
};