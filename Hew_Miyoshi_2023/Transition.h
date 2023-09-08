#pragma once
#include "gameObject.h"

/**
 * @brief 画面遷移用のクラス
 */
class Transition : public GameObject
{
public:
    /**
     * @brief 画面遷移の状態を表す列挙型
     */
    enum class State
    {
        Stop,   ///< フェードイン終了
        In,     ///< フェードイン
        Out,    ///< フェードアウト
        Finish  ///< フェードアウト終了
    };

private:
    float m_Alpha = 0.0f;         ///< 透明度（アルファ値）
    State m_State = State::Stop; ///< 画面遷移の状態
    class Sprite* m_Sprite{};   ///< スプライトクラスへのポインタ

public:
    /**
     * @brief 初期化関数
     */
    void Init() override;

    /**
     * @brief 更新関数
     */
    void Update() override;

    /**
     * @brief 画面遷移の状態を取得
     * @return 画面遷移の状態（State列挙型）
     */
    State GetState() { return m_State; }

    /**
     * @brief フェードインの初期処理
     */
    void FadeIn()
    {
        m_Alpha = 1.0f;
        m_State = State::In;
    }

    /**
     * @brief フェードアウトの初期処理
     */
    void FadeOut()
    {
        m_Alpha = 0.0f;
        m_State = State::Out;
    }
};
