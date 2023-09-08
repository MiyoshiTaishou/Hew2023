#pragma once

#include "renderer.h"
#include <list>
#include <SimpleMath.h>
#include "component.h"

/**
 * @brief ゲームオブジェクトの基本クラスです。
 */
class GameObject
{
protected:
    bool m_Destroy = false; ///< オブジェクトの破棄フラグ
    DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f); ///< オブジェクトの位置
    DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f); ///< オブジェクトの回転
    DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f); ///< オブジェクトのスケール

    std::list<Component*> m_Component; ///< オブジェクトにアタッチされたコンポーネントのリスト
    std::list<GameObject*> m_ChildGameObject; ///< 子オブジェクトのリスト

public:
    /**
     * @brief GameObjectクラスのコンストラクタ
     */
    GameObject() {}

    /**
     * @brief GameObjectクラスのデストラクタ
     */
    virtual ~GameObject() {}

    /**
     * @brief オブジェクトの位置を取得します。
     * @return オブジェクトの位置
     */
    DirectX::SimpleMath::Vector3 GetPosition() { return m_Position; }

    /**
     * @brief オブジェクトの回転を取得します。
     * @return オブジェクトの回転
     */
    DirectX::SimpleMath::Vector3 GetRotation() { return m_Rotation; }

    /**
     * @brief オブジェクトのスケールを取得します。
     * @return オブジェクトのスケール
     */
    DirectX::SimpleMath::Vector3 GetScale() { return m_Scale; }

    /**
     * @brief オブジェクトの位置を設定します。
     * @param Position 新しい位置
     */
    void SetPosition(DirectX::SimpleMath::Vector3 Position) { m_Position = Position; }

    /**
     * @brief オブジェクトの回転を設定します。
     * @param Rotation 新しい回転
     */
    void SetRotation(DirectX::SimpleMath::Vector3 Rotation) { m_Rotation = Rotation; }

    /**
     * @brief オブジェクトのスケールを設定します。
     * @param Scale 新しいスケール
     */
    void SetScale(DirectX::SimpleMath::Vector3 Scale) { m_Scale = Scale; }

    /**
     * @brief オブジェクトの前方ベクトルを取得します。
     * @return オブジェクトの前方ベクトル
     */
    DirectX::SimpleMath::Vector3 GetForward()
    {
        // 前方ベクトルを計算する処理
        DirectX::SimpleMath::Matrix rot;
        rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);

        DirectX::SimpleMath::Vector3 forward;
        forward.x = rot._31;
        forward.y = rot._32;
        forward.z = rot._33;

        return forward;
    }

    /**
     * @brief オブジェクトの横方向ベクトルを取得します。
     * @return オブジェクトの横方向ベクトル
     */
    DirectX::SimpleMath::Vector3 GetSide()
    {
        // 横方向ベクトルを計算する処理
        DirectX::SimpleMath::Matrix rot;
        rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(m_Rotation.y - 89.535f, m_Rotation.x, m_Rotation.z);

        DirectX::SimpleMath::Vector3 side;
        side.x = rot._31;
        side.y = rot._32;
        side.z = rot._33;

        return side;
    }

    /**
     * @brief オブジェクトの破棄フラグを設定します。
     */
    void SetDestroy() { m_Destroy = true; }

    /**
     * @brief オブジェクトを破棄します。
     * @return オブジェクトが破棄された場合はtrue、それ以外はfalse
     */
    bool Destroy()
    {
        if (m_Destroy)
        {
            UninitBase();
            delete this;
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief オブジェクトの初期化を行います。
     */
    virtual void Init() {}

    /**
     * @brief オブジェクトの終了処理を行います。
     */
    virtual void Uninit() {}

    /**
     * @brief オブジェクトの更新処理を行います。
     */
    virtual void Update() {}

    /**
     * @brief オブジェクトの描画処理を行います。
     */
    virtual void Draw() {}

    /**
     * @brief オブジェクトに新しいコンポーネントを追加します。
     * @tparam T 追加するコンポーネントの型
     * @return 追加されたコンポーネントへのポインタ
     */
    template <typename T>
    T* AddComponent()
    {
        T* component = new T(this);
        m_Component.push_back(component);
        ((Component*)component)->Init();

        return component;
    }

    /**
     * @brief オブジェクトから指定された型のコンポーネントを取得します。
     * @tparam T 取得するコンポーネントの型
     * @return コンポーネントへのポインタ
     */
    template <typename T>
    T* GetComponent()
    {
        for (Component* component : m_Component)
        {
            if (typeid(*component) == typeid(T))
            {
                return (T*)component;
            }
        }
        return nullptr;
    }

    /**
     * @brief 子オブジェクトを追加します。
     * @tparam T 追加する子オブジェクトの型
     * @return 追加された子オブジェクトへのポインタ
     */
    template <typename T>
    T* AddChild()
    {
        T* child = new T();
        m_ChildGameObject.push_back(child);
        child->InitBase();

        return child;
    }

    /**
     * @brief オブジェクトとその子オブジェクト、コンポーネントを初期化します。
     */
    void InitBase()
    {
        Init();
    }

    /**
     * @brief オブジェクトとその子オブジェクト、コンポーネントを終了処理します。
     */
    void UninitBase()
    {
        Uninit();

        for (GameObject* child : m_ChildGameObject)
        {
            child->UninitBase();
            delete child;
        }

        for (Component* component : m_Component)
        {
            component->Uninit();
            delete component;
        }
        m_Component.clear(); // リストのクリア
        m_ChildGameObject.clear();
    }

    /**
     * @brief オブジェクトとその子オブジェクト、コンポーネントを更新します。
     */
    void UpdateBase()
    {
        for (GameObject* child : m_ChildGameObject)
        {
            child->UpdateBase();
        }

        for (Component* component : m_Component)
        {
            component->Update();
        }

        Update();
    }

    /**
     * @brief オブジェクトとその子オブジェクト、コンポーネントを描画します。
     * @param ParentMatrix 親オブジェクトのワールド行列
     */
    void DrawBase(DirectX::SimpleMath::Matrix ParentMatrix)
    {
        // マトリクス設定
        DirectX::SimpleMath::Matrix world, scale, rot, trans;
        scale = DirectX::SimpleMath::Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);
        rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
        trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
        world = scale * rot * trans * ParentMatrix;

        for (GameObject* child : m_ChildGameObject)
        {
            child->DrawBase(world);
        }

        Renderer::SetWorldMatrix(&world);

        for (Component* component : m_Component)
        {
            component->Draw();
        }

        Draw();
    }
};