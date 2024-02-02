#pragma once
#include"scene.h"

//�R����p�⓹�]�����I�V�[��

class Particle;

class SlopeScene : public Scene
{
    class Transition* m_Transition{};

    //�V�[���J�ڃt���O
    bool m_Goal = false;

    Particle* m_Particle;

    DirectX::SimpleMath::Vector3 m_Pos;
    DirectX::SimpleMath::Vector3 m_Dir;
    DirectX::SimpleMath::Vector3 m_Speed;
    float m_Life;
    float m_Scale;
    bool m_Fade = true;
public:
    void Init()override;
    void Uninit()override;
    void Draw()override;
    void Update()override;

private:
};