#pragma once
#include <cinttypes>
#include "../Scene/scene.h"

// 前方参照
class Application;

class Manager
{
private:
    static class Scene* m_Scene; // 現在のシーンへのポインタ

    //ゲームシーン
    static std::string m_FiledName;
    static std::string m_MapName;
    static std::string m_SkyName;

    //BGMリスト
    static std::vector<std::string> m_BGMList;

    static int m_Count;//たこ焼きの数
    static int m_CountMax;//たこ焼きの数

    static bool m_End;

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

    //たこ焼きに数を追加
    static void AddCount(int _count)
    {
        m_Count += _count;
    }

    static int GetCount()
    {
        return m_Count;
    }

    static int GetCountMax()
    {
        return m_CountMax;
    }

    static std::string GetFiledName()
    {
        return m_FiledName;
    }

    static std::string GetMapName()
    {
        return m_MapName;
    }

    static std::string GetSkyName()
    {
        return m_SkyName;
    }

    static bool GetEnd()
    {
        return m_End;
    }

    static std::vector<std::string> GetBGMList()
    {
        return m_BGMList;
    }

    static void SetCountMax(int _count)
    {
        m_CountMax = _count;
    }

    static void InitCount()
    {
        m_Count = 0;
    }

    static void SetFiledName(std::string _text) 
    {
        m_FiledName = _text;
    }

    static void SetMapName(std::string _text)
    {
        m_MapName = _text;
    }

    static void SetSkyName(std::string _text)
    {
        m_SkyName = _text;
    }

    static void SetEnd(bool _end)
    {
        m_End = _end;
    }  

    static void SetBGMList(std::vector<std::string> _list)
    {
        m_BGMList = _list;
    }
};
