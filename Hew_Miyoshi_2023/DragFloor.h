#pragma once
#include "gameObject.h"

/**
 * @brief 摩擦係数を変える床
 *
 * このクラスは摩擦係数を変更する床を表します。滑りやすい（にくい）床として使用できます。
 */
class DragFloor : public GameObject
{
public:
    /**
     * @brief 床の初期化
     *
     * 床の初期化処理を行います。
     */
    void Init();
};
