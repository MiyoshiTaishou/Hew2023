#pragma once

#include "gameObject.h"

/**
 * @brief デバッグ用カメラクラス
 *
 * このクラスはデバッグ用のカメラを表します。
 */
class DebugCamera : public GameObject {
private:
    DirectX::SimpleMath::Vector3 m_Target{}; ///< カメラのターゲット位置
    DirectX::SimpleMath::Matrix m_ViewMatrix{}; ///< カメラのビュー行列
    DirectX::SimpleMath::Vector3 m_Forward{}; ///< カメラの前方ベクトル

public:
   
    void Init();
    void Uninit();
    void Update();
    void Draw();

    /**
     * @brief カメラのターゲット位置を設定する
     *
     * @param target 新しいカメラのターゲット位置
     */
    void SetTarget(DirectX::SimpleMath::Vector3 target);

    /**
     * @brief カメラのビュー行列を取得する
     *
     * @return カメラのビュー行列
     */
    DirectX::SimpleMath::Matrix GetViewMatrix() {
        return m_ViewMatrix;
    }
};
