#pragma once
#include "scene.h"

enum SELECT_SCENE
{
    TUTORIAL,
    GAME1,
    GAME2,
};

class TitleScene : public Scene
{
private:
    class Transition* m_Transition{}; 

    //シーン遷移フラグ
    bool m_Goal = false;

    float currentTime = 1.0f;// 現在の時間を取得する処理（例えば、DirectXの時間関数を使用する）

    // 時間をシェーダーに送信するための定数バッファの作成
    ID3D11Buffer* timeBuffer;
    D3D11_BUFFER_DESC timeBufferDesc;

    // データを入れるための構造体を作成し、データを設定する場合
    D3D11_SUBRESOURCE_DATA timeBufferData;

    //SE鳴らす
    GameObject* m_SEObj;

    SELECT_SCENE m_Select;

    GameObject* m_TitleSprite[3];

    MATERIAL m_TitleMt;
    MATERIAL m_AnyKeyMT;

    bool m_UpDown = true;
    bool m_FadeStart = false;

public:
    void Init()override;
    void Update()override;   

    //タイトル画面のフェード処理
    bool FadeTitle();
};

