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
    DirectX::SimpleMath::Matrix m_ProjMatrix{}; ///< カメラのプロジェクション行列
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

    DirectX::SimpleMath::Matrix GetProjMatrix()
    {
        return m_ProjMatrix;
    }

    float theta = 30; // 水平方向の角度
    float phi = 30; // 垂直方向の角度

    DirectX::SimpleMath::Vector3 camForward;
    DirectX::SimpleMath::Vector3 camRight;
};
