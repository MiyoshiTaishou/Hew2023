#pragma once
#include <list>
#include <array>
#include <vector>
#include <typeinfo>
#include "../Object/gameObject.h"
#include "../Render/modelRenderer.h"

/**
 * @brief シーン管理クラス
 */
class Scene
{
protected:
    // STLのリスト構造
    std::array<std::list<GameObject*>, 4> m_GameObject;

public:
    /**
     * @brief Sceneクラスのコンストラクタ
     */
    Scene() {}

    /**
     * @brief Sceneクラスのデストラクタ
     */
    virtual ~Scene() {}

    /**
     * @brief シーンの初期化を行います。
     */
    virtual void Init() {}

    /**
     * @brief シーンの終了処理を行います。
     */
    virtual void Uninit() {}

    /**
     * @brief シーンの更新処理を行います。
     */
    virtual void Update() {}

    /**
     * @brief シーンの描画処理を行います。
     */
    virtual void Draw() {}

    /**
     * @brief シーンの基本初期化処理を行います。
     */
    void InitBase()
    {
        Init();
    }

    /**
     * @brief シーンの基本終了処理を行います。
     */
    void UninitBase()
    {
        for (auto& objectList : m_GameObject)
        {
            for (GameObject* object : objectList)
            {
                object->UninitBase();
                delete object;
            }
            // リストクリア
            objectList.clear();
        }

        Uninit();

        ModelRenderer::UnloadAll();
    }

    /**
     * @brief シーンの基本更新処理を行います。
     */
    void UpdateBase()
    {
        for (auto& objectList : m_GameObject)
        {
            for (GameObject* object : objectList)
            {
                object->UpdateBase();
            }
            // ラムダ式
            // 削除していいものは削除する
            objectList.remove_if([](GameObject* object) { return object->Destroy(); });
        }

        Update();
    }

    /**
     * @brief シーンの基本描画処理を行います。
     */
    void DrawBase()
    {
        DirectX::SimpleMath::Matrix matrix;
        matrix = DirectX::SimpleMath::Matrix::Identity;

        for (auto& objectList : m_GameObject)
        {
            for (GameObject* object : objectList)
            {
                object->DrawBase(matrix);
            }
        }

        Draw();
    }

    /**
     * @brief 指定したレイヤーに新しいGameObjectを追加します。
     * @tparam T 追加するGameObjectの型
     * @param Layer レイヤー番号
     * @return 追加されたGameObjectへのポインタ
     */
    template <typename T>
    T* AddGameObject(int Layer)
    {
        T* gameObject = new T();
        m_GameObject[Layer].push_back(gameObject);
        gameObject->Init();

        return gameObject;
    }

    /**
     * @brief 指定した型のGameObjectを取得します。
     * @tparam T 取得するGameObjectの型
     * @return GameObjectへのポインタ
     */
    template <typename T>
    T* GetGameObject()
    {
        for (auto& objectList : m_GameObject)
        {
            for (GameObject* object : objectList)
            {
                if (typeid(*object) == typeid(T)) // 型を調べる (RTTI動的型情報)
                {
                    return (T*)object;
                }
            }
        }

        return nullptr;
    }

    /**
     * @brief 指定した型のすべてのGameObjectを取得します。
     * @tparam T 取得するGameObjectの型
     * @return GameObjectのベクター
     */
    template <typename T>
    std::vector<T*> GetGameObjects()
    {
        std::vector<T*> objects; // STL配列

        for (auto& objectList : m_GameObject)
        {
            for (GameObject* object : objectList)
            {
                if (typeid(*object) == typeid(T))
                {
                    objects.push_back((T*)object);
                }
            }
        }

        return objects;
    }
};
