#pragma once
#include "scene.h"
#include "StageEditor.h"

/**
 * @brief ゲームシーン Game クラス
 */
class Game : public Scene
{
private:
    class Transition* m_Transition{}; /**< 画面遷移を管理するオブジェクト */
    class FadeUI* m_Fade{}; /**< フェードUIを管理するオブジェクト */

    bool m_Goal = false; /**< ゴールしているかどうかを示すフラグ */

public:
    /**
     * @brief ゲームシーンの初期化関数
     */
    void Init() override;

    /**
     * @brief ゲームシーンの更新関数
     */
    void Update() override;

    /**
     * @brief StageEditor シーンで作成したステージをファイルからロードする関数
     * @param filename ファイル名
     */
    void LoadpositionToFile(const std::string& filename);
};
