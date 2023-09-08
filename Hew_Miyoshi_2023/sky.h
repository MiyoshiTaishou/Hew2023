#pragma once

#include "gameObject.h"
#include "renderer.h"

/**
 * @brief 背景オブジェクトプレイヤーについてくる Sky クラス
 */
class Sky : public GameObject
{

private:
    Bloom bloom; /**< Bloom エフェクトを管理するオブジェクト */
    RotationAngle rot; /**< 回転角度を管理するオブジェクト */

public:
  
    void Init() override;
    void Update() override;  
    void Draw() override;
};
