/**
 * @file Transition.h
 *
 * @brief このファイルは Transition クラスの定義を含んでいます。
 */

#pragma once

#include "gameObject.h"

 /**
  * @class Transition
  *
  * @brief Transition クラスは、フェードインとフェードアウトのエフェクトを持つゲーム遷移を表します。
  */
class Transition : public GameObject
{
public:

    /**
     * @brief 遷移の可能な状態を表す列挙型です。
     */
    enum class State
    {
        Stop,   ///< フェードイン終了
        In,     ///< フェードイン
        Out,    ///< フェードアウト
        Finish  ///< フェードアウト終了
    };

private:
    float m_Alpha = 0.0f; ///< フェード効果を制御するアルファ値です。
    State m_State = State::Stop; ///< 遷移の現在の状態です。
    class Sprite* m_Sprite{}; ///< 遷移に関連付けられたスプライトへのポインタです。

public:

    /**
     * @brief 遷移オブジェクトを初期化します。
     */
    void Init() override;

    /**
     * @brief 遷移オブジェクトを更新します。
     */
    void Update() override;

    /**
     * @brief 遷移の現在の状態を取得します。
     *
     * @return 遷移の現在の状態。
     */
    State GetState() { return m_State; }

    /**
     * @brief フェードインを初期化します。
     */
    void FadeIn()
    {
        m_Alpha = 1.0f;
        m_State = State::In;
    }

    /**
     * @brief フェードアウトを初期化します。
     */
    void FadeOut()
    {
        m_Alpha = 0.0f;
        m_State = State::Out;
    }
};
