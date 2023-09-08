#pragma once
#include "gameObject.h"

/**
 * @brief 上に乗ると跳ねるオブジェクト Trampoline クラス
 */
class Trampoline : public GameObject
{
public:
 
    void Init() override;

    /**
     * @brief 跳ねる強さを設定する
     * @param _power 跳ねる強さ
     */
    void SetPower(float _power);

    /**
     * @brief オブジェクトを跳ねさせる
     * @param obj 跳ねさせる対象の GameObject
     */
    void Action(GameObject* obj);

private:
    float power = 300.0f; /**< 跳ねる強さ */
};
