#pragma once
#include <cinttypes>
#include "scene.h"

// 前方参照
class Application;

/**
 * @brief シーンにあるオブジェクトを管理し、描画するクラス
 */
class Manager
{
private:

    // 現在のシーン
    static class Scene* m_Scene;

public:

    /**
     * @brief Managerクラスの初期化
     * @param[in] ap Applicationクラスへのポインタ
     */
    static void Init(Application* ap);

    /**
     * @brief Managerクラスの終了処理
     */
    static void Uninit();

    /**
     * @brief Managerクラスの更新処理
     * @param[in] d 更新にかかる時間（ミリ秒）
     */
    static void Update(uint64_t d);

    /**
     * @brief Managerクラスの描画処理
     * @param[in] d 描画にかかる時間（ミリ秒）
     */
    static void Draw(uint64_t d);

    /**
     * @brief 現在のシーンを取得する
     * @return 現在のシーンへのポインタ
     */
    static class Scene* GetScene()
    {
        return m_Scene;
    }

    /**
     * @brief 新しいシーンを設定する
     * @tparam T 新しいシーンの型
     */
    template <typename T>
    static void SetScene()
    {
        if (m_Scene)
        {
            m_Scene->UninitBase();
            delete m_Scene;
        }

        m_Scene = new T();
        m_Scene->InitBase();
    }
};
