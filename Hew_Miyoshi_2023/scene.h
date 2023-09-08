#pragma once
#include <list>
#include <array>
#include <vector>
#include <typeinfo>
#include "gameObject.h"
#include "modelRenderer.h"

/**
 * @brief シーン管理クラス Scene
 */
class Scene
{
protected:
    std::array<std::list<GameObject*>, 4> m_GameObject; /**< ゲームオブジェクトのリスト構造 */

public:
    /**
     * @brief コンストラクタ
     */
    Scene() {}

    /**
     * @brief デストラクタ
     */
    virtual ~Scene() {}

    /**
     * @brief シーンの初期化関数
     */
    virtual void Init() {}

    /**
     * @brief シーンの終了関数
     */
    virtual void Uninit() {}

    /**
     * @brief シーンの更新関数
     */
    virtual void Update() {}

    /**
     * @brief シーンの描画関数
     */
    virtual void Draw() {}

    /**
     * @brief 基本の初期化関数
     */
    void InitBase()
    {
        Init();
    }

    /**
     * @brief 基本の終了関数
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
            objectList.clear();
        }

        Uninit();

        ModelRenderer::UnloadAll();
    }

    /**
     * @brief 基本の更新関数
     */
    void UpdateBase()
    {
        for (auto& objectList : m_GameObject)
        {
            for (GameObject* object : objectList)
            {
                object->UpdateBase();
            }
            objectList.remove_if([](GameObject* object) { return object->Destroy(); });
        }

        Update();
    }

    /**
     * @brief 基本の描画関数
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
     * @brief ゲームオブジェクトを追加するテンプレート関数
     * @tparam T 追加するゲームオブジェクトの型
     * @param Layer ゲームオブジェクトのレイヤ
     * @return 追加されたゲームオブジェクトのポインタ
     */
    template<typename T>
    T* AddGameObject(int Layer)
    {
        T* gameObject = new T();
        m_GameObject[Layer].push_back(gameObject);
        gameObject->Init();

        return gameObject;
    }

    /**
     * @brief 特定の型のゲームオブジェクトを取得するテンプレート関数
     * @tparam T 取得したいゲームオブジェクトの型
     * @return 特定の型のゲームオブジェクトのポインタ
     */
    template<typename T>
    T* GetGameObject()
    {
        for (auto& objectList : m_GameObject)
        {
            for (GameObject* object : objectList)
            {
                if (typeid(*object) == typeid(T))
                {
                    return (T*)object;
                }
            }
        }

        return nullptr;
    }

    /**
     * @brief 特定の型のゲームオブジェクトを取得するテンプレート関数
     * @tparam T 取得したいゲームオブジェクトの型
     * @return 特定の型のゲームオブジェクトのポインタのベクター
     */
    template<typename T>
    std::vector<T*> GetGameObjects()
    {
        std::vector<T*> objects;

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
