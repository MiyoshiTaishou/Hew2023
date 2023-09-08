#pragma once
#include "gameObject.h"

/**
 * @brief プレイヤーの操作で視点を移動できるカメラのクラスです。
 */
class DebugCamera : public GameObject
{
private:
    DirectX::SimpleMath::Vector3 m_Target{}; ///< カメラのターゲット座標
    DirectX::SimpleMath::Matrix m_ViewMatrix{}; ///< カメラのビュー行列
    DirectX::SimpleMath::Vector3 m_Foward{}; ///< カメラの前方ベクトル

public:
    /**
     * @brief DebugCameraクラスの初期化を行います。
     */
    void Init();

    /**
     * @brief DebugCameraクラスの更新処理を行います。
     */
    void Update();

    /**
     * @brief DebugCameraクラスの描画処理を行います。
     */
    void Draw();

    /**
     * @brief カメラのターゲット座標を設定します。
     * @param target ターゲット座標
     */
    void SetTarget(DirectX::SimpleMath::Vector3 target);

    /**
     * @brief カメラのビュー行列を取得します。
     * @return カメラのビュー行列
     */
    DirectX::SimpleMath::Matrix GetViewMatrix()
    {
        return m_ViewMatrix;
    }
};
