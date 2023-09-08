#pragma once
#include <cinttypes>
#include "scene.h"

// 前方参照
class Application;

class Manager
{
private:
    static class Scene* m_Scene; // 現在のシーンへのポインタ

public:
    /**
     * @brief Managerクラスの初期化
     * @param ap アプリケーションへのポインタ
     */
    static void Init(Application* ap);

    /**
     * @brief Managerクラスの終了処理
     */
    static void Uninit();

    /**
     * @brief Managerクラスの更新
     * @param d 経過時間
     */
    static void Update(uint64_t d);

    /**
     * @brief Managerクラスの描画
     * @param d 経過時間
     */
    static void Draw(uint64_t d);

    /**
     * @brief 現在のシーンを取得します。
     * @return 現在のシーンへのポインタ
     */
    static class Scene* GetScene()
    {
        return m_Scene;
    }

    /**
     * @brief 新しいシーンを設定します。
     * @tparam T 設定する新しいシーンのクラス型
     */
    template <typename T>
    static void SetScene()
    {
        // 現在のシーンをクリアして新しいシーンを設定
        if (m_Scene)
        {
            m_Scene->UninitBase();
            delete m_Scene;
        }

        m_Scene = new T();
        m_Scene->InitBase();
    }
};
