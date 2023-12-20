#pragma once
#include"scene.h"

class ResultScene : public Scene
{
    class Transition* m_Transition{};

    //シーン遷移フラグ
    bool m_Goal = false;

    //たこ焼きテクスチャ
    std::vector<GameObject*> m_SpriteObj;

    //何番目のテクスチャか
    int m_SpriteNo = 0;

    //マテリアル
    MATERIAL m_Mt;

    //結果発表テクスチャ
    GameObject* m_ResultTex;

    //スキップ
    bool m_Skip = false;

    //SE
    GameObject* m_SE[8];

public:
    void Init()override;
    void Update()override;
};