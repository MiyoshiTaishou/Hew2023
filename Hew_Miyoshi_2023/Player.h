#pragma once
#include "gameObject.h"
#include <SimpleMath.h>
#include <vector>
#include "GamePad.h"

/**
 * @brief プレイヤーキャラクター
 *
 * このクラスはプレイヤーキャラクターを表します。
 */
class Player : public GameObject
{
public:
    /**
     * @brief プレイヤーの初期化
     *
     * プレイヤーキャラクターの初期化処理を行います。
     */
    void Init() override;

    /**
     * @brief プレイヤーの終了処理
     *
     * プレイヤーキャラクターの終了処理を行います。
     */
    void Uninit() override;

    /**
     * @brief プレイヤーの更新
     *
     * プレイヤーキャラクターの状態を更新する処理を行います。
     */
    void Update() override;

    /**
     * @brief プレイヤーの描画
     *
     * プレイヤーキャラクターの描画処理を行います。
     */
    void Draw() override;

    DirectX::GamePad::State buttonState; ///< プレイヤーキャラクターのボタン状態

private:
    DirectX::SimpleMath::Vector3 m_Velocity{}; ///< プレイヤーキャラクターの速度
    class Audio* m_SE{}; ///< 効果音オブジェクト
    class Audio* m_MeatSE{}; ///< 当たったときの効果音オブジェクト
    class Audio* m_MeatSE2{}; ///< 当たったときの効果音オブジェクト（2つ目）

    std::list<GameObject*> m_Children; ///< プレイヤーキャラクターの子オブジェクトリスト
    GameObject* mchild; ///< 子オブジェクト

    // 塊の大きさ
    float m_Size;

    // ダッシュ用変数
    int loopCount = 0;
    int reception = 60;
    int actionCount = 0;
    int actionDashu = 5;
    bool actionCheck = false;

    // 壁登り用変数
    bool wallUp = false;

    // 頂点座標
    std::vector<DirectX::SimpleMath::Vector3> m_VertexPos;
};
