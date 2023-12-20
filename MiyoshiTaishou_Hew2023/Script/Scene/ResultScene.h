#pragma once
#include"scene.h"

class ResultScene : public Scene
{
    class Transition* m_Transition{};

    //�V�[���J�ڃt���O
    bool m_Goal = false;

    //�����Ă��e�N�X�`��
    std::vector<GameObject*> m_SpriteObj;

    //���Ԗڂ̃e�N�X�`����
    int m_SpriteNo = 0;

    //�}�e���A��
    MATERIAL m_Mt;

    //���ʔ��\�e�N�X�`��
    GameObject* m_ResultTex;

    //�X�L�b�v
    bool m_Skip = false;

    //SE
    GameObject* m_SE[8];

public:
    void Init()override;
    void Update()override;
};