#pragma once
#include "gameObject.h"

/**
 * @brief プレイヤーに当たるとくっつく敵
 *
 * このクラスはプレイヤーに当たるとくっつく敵を表します。
 */
class Enemy : public GameObject
{
public:
    /**
     * @brief 敵の初期化
     *
     * 敵の初期化処理を行います。
     */
    void Init() override;

    /**
     * @brief 敵の更新
     *
     * 敵の状態を更新する処理を行います。
     */
    void Update() override;
};
