#pragma once
#include <list>
#include <array>
#include <vector>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../Object/gameObject.h"
#include"../Object/BoxObject.h"
#include"../Object/Player.h"

//ステージ用オブジェクト
#include"../Object/YataiObject.h"
#include"../Object/YakisobaObject.h"
#include"../Object/TreeObject.h"
#include"../Object/KasuteraObject.h"
#include"../Object/CarObject.h"
#include"../Object/field.h"

#include "../Render/modelRenderer.h"
#include"../Particle/Particle.h"

//たこ焼きの最大数
#define MAX_SPHERE 10

enum OBJTAG
{
    BOX,
    YATAI,
    YAKISOBA,
    TREE,
    KASUTERA,
    CAR,
    FILED,
};

enum Layer
{
    Layer0,
    Layer1,
    Layer2,
    Layer3,
};
/**
 * @brief シーン管理クラス
 */
class Scene
{
protected:
    // STLのリスト構造
    std::array<std::list<GameObject*>, 4> m_GameObject;    

public:

    std::vector<Particle*> m_Particle;

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

        for (Particle* particl : m_Particle)
        {
            particl->Init();
        }
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

        for (Particle* particl : m_Particle)
        {
            particl->Uninit();
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

        for (Particle* particl : m_Particle)
        {
            particl->Update();
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

      /*  for (Particle* particl : m_Particle)
        {
            particl->Draw();
        }*/
        
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

    // オブジェクトデータをCSV形式で保存する関数
    void SaveObjectData(const std::string& filename)
    {
        std::ofstream outputFile(filename);

        if (!outputFile.is_open())
        {
            std::cerr << "Error: Unable to open file for writing." << std::endl;
            return;
        }

        const auto& objList = m_GameObject[Layer1];

        outputFile << "Tag,PosX,PosY,PosZ,ScaleX,ScaleY,ScaleZ,RotX,RotY,RotZ\n";
      
        for (const auto& obj : objList)
        {
            if (typeid(*obj) == typeid(BoxObject))
            {
                outputFile << OBJTAG::BOX;
            }               
            if (typeid(*obj) == typeid(YataiObject))
            {
                outputFile << OBJTAG::YATAI;
            }
            if (typeid(*obj) == typeid(YakisobaObject))
            {
                outputFile << OBJTAG::YAKISOBA;
            }
            if (typeid(*obj) == typeid(TreeObject))
            {
                outputFile << OBJTAG::TREE;
            }
            if (typeid(*obj) == typeid(KasuteraObject))
            {
                outputFile << OBJTAG::KASUTERA;
            }
            if (typeid(*obj) == typeid(CarObject))
            {
                outputFile << OBJTAG::CAR;
            }
            if (typeid(*obj) == typeid(Field))
            {
                outputFile << OBJTAG::FILED;
            }
            
            outputFile << "," << obj->GetPosition().x << "," << obj->GetPosition().y << "," << obj->GetPosition().z << ","
                << obj->GetScale().x << "," << obj->GetScale().y << "," << obj->GetScale().z << ","
                << obj->GetRotation().x << "," << obj->GetRotation().y << "," << obj->GetRotation().z << "\n";
        }                                         

        outputFile.close();
    }

    // CSV形式のデータからオブジェクトデータを読み込む関数
    void LoadObjectData(const std::string& filename)
    {        
        std::ifstream inputFile(filename);

        if (!inputFile.is_open())
        {
            return;
        }

        const auto& objList = m_GameObject[Layer1];
        for (const auto& obj : objList)
        {
            if (typeid(*obj) != typeid(Player)) // 型を調べる
            {
                obj->SetDestroy();
            }            
        }

        //ヘッダを捨てる
        std::string header;
        std::getline(inputFile, header);

        std::string line;
        while (std::getline(inputFile, line))
        {            
            std::istringstream ss(line);
            std::string token;

            OBJTAG tag;
            DirectX::SimpleMath::Vector3 pos;
            DirectX::SimpleMath::Vector3 scale;
            DirectX::SimpleMath::Vector3 rot;

            //std::getline(ss, token, '\n');

            // カンマ区切りでデータを取得
            std::getline(ss, token, ',');
            int tagValue = std::stoi(token);

            tag = static_cast<OBJTAG>(tagValue);

            std::getline(ss, token, ',');
            pos.x = std::stof(token);
            std::getline(ss, token, ',');
            pos.y = std::stof(token);
            std::getline(ss, token, ',');
            pos.z = std::stof(token);

            std::getline(ss, token, ',');
            scale.x = std::stof(token);
            std::getline(ss, token, ',');
            scale.y = std::stof(token);
            std::getline(ss, token, ',');
            scale.z = std::stof(token);

            std::getline(ss, token, ',');
            rot.x = std::stof(token);
            std::getline(ss, token, ',');
            rot.y = std::stof(token);
            std::getline(ss, token, '\n');
            rot.z = std::stof(token); 

            switch (tag)
            {
            case BOX:
            {
                BoxObject* obj = AddGameObject<BoxObject>(Layer1);
                obj->SetPosition(pos);
                obj->SetScale(scale);
                obj->SetRotation(rot);
                break;
            }
            case YATAI:
            {
                YataiObject* obj = AddGameObject<YataiObject>(Layer1);
                obj->SetPosition(pos);
                obj->SetScale(scale);
                obj->SetRotation(rot);
                break;
            }
            case YAKISOBA:
            {
                YakisobaObject* obj = AddGameObject<YakisobaObject>(Layer1);
                obj->SetPosition(pos);
                obj->SetScale(scale);
                obj->SetRotation(rot);
                break;
            }
            case TREE:
            {
                TreeObject* obj = AddGameObject<TreeObject>(Layer1);
                obj->SetPosition(pos);
                obj->SetScale(scale);
                obj->SetRotation(rot);
                break;
            }
            case KASUTERA:
            {
                KasuteraObject* obj = AddGameObject<KasuteraObject>(Layer1);
                obj->SetPosition(pos);
                obj->SetScale(scale);
                obj->SetRotation(rot);
                break;
            }
            case CAR:
            {
                CarObject* obj = AddGameObject<CarObject>(Layer1);
                obj->SetPosition(pos);
                obj->SetScale(scale);
                obj->SetRotation(rot);
                break;
            }
            case FILED:
            {
                Field* obj = AddGameObject<Field>(Layer1);
                obj->SetPosition(pos);
                obj->SetScale(scale);
                obj->SetRotation(rot);
                break;
            }
            default:
                break;
            }
        }

        inputFile.close();
        return;
    }
};
