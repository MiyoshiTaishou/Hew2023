#pragma once
#include "gameObject.h"
#include "renderer.h"

/**
 * @brief フェードUIオブジェクト
 */
class FadeUI : public GameObject
{
public:
   
    void Init();
    void Update();

    //状態
    enum class State
    {
        Stop,//フェードイン終了
        In,//フェードイン
        Out,//フェードアウト
        Finish//フェードアウト終了
    };

    /**
     * @brief フェードUIの状態を取得する
     * @return フェードUIの状態
     */
    State GetState() { return m_State; }

    /**
     * @brief フェードイン処理を開始する
     */
    void FadeIn()
    {
        m_Alpha = 1.0f;
        m_State = State::In;
    }

    /**
     * @brief フェードアウト処理を開始する
     */
    void FadeOut()
    {
        m_Alpha = 0.0f;
        m_State = State::Out;
    }

private:
    Fade fade;
    float time = 0.0f;

    float m_Alpha = 0.0f;
    State m_State = State::Stop;
    class Sprite* m_Sprite{};
};
