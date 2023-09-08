#pragma once
#include <SimpleMath.h>
#include "gameObject.h"

/**
 * @brief カメラオブジェクトコンポーネントで切り替え可能なカメラのクラスです。
 */
class Camera : public GameObject
{
private:
    DirectX::SimpleMath::Vector3 m_Target{}; ///< カメラのターゲット座標
    DirectX::SimpleMath::Matrix m_ViewMatrix{}; ///< カメラのビュー行列
    DirectX::SimpleMath::Vector3 m_Foward{}; ///< カメラの前方ベクトル

public:
    /**
     * @brief Cameraクラスの初期化を行います。
     */
    void Init();

    /**
     * @brief Cameraクラスの更新処理を行います。
     */
    void Update();

    /**
     * @brief Cameraクラスの描画処理を行います。
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
