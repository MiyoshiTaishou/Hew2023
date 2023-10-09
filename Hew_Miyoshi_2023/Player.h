#pragma once

#include "gameObject.h"
#include <SimpleMath.h>
#include <vector>
#include "GamePad.h"

/**
 * @brief 操作するキャラクターのクラスです。
 */
class Player : public GameObject
{
public:
    /**
     * @brief プレイヤーオブジェクトの初期化を行います。
     */
    void Init() override;

    /**
     * @brief プレイヤーオブジェクトの更新処理を行います。
     */
    void Update() override;

    /**
     * @brief プレイヤーオブジェクトの描画処理を行います。
     */
    void Draw() override;

    /**
    * @brief プレイヤーオブジェクトのコントローラー処理を行います。
    */
    void ConInput();

    /**
    * @brief プレイヤーオブジェクトの当たり判定処理を行います。
    */
    void Collison();

private:
    /**
     * @brief プレイヤーの速度ベクトルです。
     */
    DirectX::SimpleMath::Vector3 m_Velocity{};

    /**
     * @brief SE（効果音）を再生するためのオブジェクトです。
     */
    class Audio* m_SE{};

    /**
     * @brief 肉のSE（効果音）を再生するためのオブジェクトです。
     */
    class Audio* m_MeatSE{};

    /**
     * @brief もう一つの肉のSE（効果音）を再生するためのオブジェクトです。
     */
    class Audio* m_MeatSE2{};

    /**
     * @brief 子オブジェクトのリストです。
     */
    std::list<GameObject*> m_Children;

    /**
     * @brief 子オブジェクトの一つです。
     */
    GameObject* mchild;

    /**
     * @brief 塊の大きさです。
     */
    float m_Size;

    /**
     * @brief ダッシュ用のカウント変数です。
     */
    int loopCount = 0;

    /**
     * @brief ダッシュの受付時間を表す変数です。
     */
    int reception = 60;

    /**
     * @brief アクションのカウント変数です。
     */
    int actionCount = 0;

    /**
     * @brief ダッシュアクション用のカウント変数です。
     */
    int actionDashu = 5;

    /**
     * @brief アクションの有効性を示すフラグです。
     */
    bool actionCheck = false;

    /**
     * @brief 壁を登るためのフラグです。
     */
    bool wallUp = false;

    /**
     * @brief前回の座標を保存する変数
     */
    DirectX::SimpleMath::Vector3 m_OldPos;

    /**
     * @brief 頂点座標のリストです。
     */
    std::vector<DirectX::SimpleMath::Vector3> m_VertexPos;
};
