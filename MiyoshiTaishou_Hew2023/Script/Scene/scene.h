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

#include "../Render/modelRenderer.h"

enum OBJTAG
{
    BOX,
};

enum Layer
{
    Layer0,
    Layer1,
    Layer2,
    Layer3,
};
/**
 * @brief �V�[���Ǘ��N���X
 */
class Scene
{
protected:
    // STL�̃��X�g�\��
    std::array<std::list<GameObject*>, 4> m_GameObject;

public:
    /**
     * @brief Scene�N���X�̃R���X�g���N�^
     */
    Scene() {}

    /**
     * @brief Scene�N���X�̃f�X�g���N�^
     */
    virtual ~Scene() {}

    /**
     * @brief �V�[���̏��������s���܂��B
     */
    virtual void Init() {}

    /**
     * @brief �V�[���̏I���������s���܂��B
     */
    virtual void Uninit() {}

    /**
     * @brief �V�[���̍X�V�������s���܂��B
     */
    virtual void Update() {}

    /**
     * @brief �V�[���̕`�揈�����s���܂��B
     */
    virtual void Draw() {}

    /**
     * @brief �V�[���̊�{�������������s���܂��B
     */
    void InitBase()
    {
        Init();
    }

    /**
     * @brief �V�[���̊�{�I���������s���܂��B
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
            // ���X�g�N���A
            objectList.clear();
        }

        Uninit();

        ModelRenderer::UnloadAll();
    }

    /**
     * @brief �V�[���̊�{�X�V�������s���܂��B
     */
    void UpdateBase()
    {
        for (auto& objectList : m_GameObject)
        {
            for (GameObject* object : objectList)
            {
                object->UpdateBase();
            }
            // �����_��
            // �폜���Ă������͍̂폜����
            objectList.remove_if([](GameObject* object) { return object->Destroy(); });
        }

        Update();
    }

    /**
     * @brief �V�[���̊�{�`�揈�����s���܂��B
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
     * @brief �w�肵�����C���[�ɐV����GameObject��ǉ����܂��B
     * @tparam T �ǉ�����GameObject�̌^
     * @param Layer ���C���[�ԍ�
     * @return �ǉ����ꂽGameObject�ւ̃|�C���^
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
     * @brief �w�肵���^��GameObject���擾���܂��B
     * @tparam T �擾����GameObject�̌^
     * @return GameObject�ւ̃|�C���^
     */
    template <typename T>
    T* GetGameObject()
    {
        for (auto& objectList : m_GameObject)
        {
            for (GameObject* object : objectList)
            {
                if (typeid(*object) == typeid(T)) // �^�𒲂ׂ� (RTTI���I�^���)
                {
                    return (T*)object;
                }
            }
        }

        return nullptr;
    }

    /**
     * @brief �w�肵���^�̂��ׂĂ�GameObject���擾���܂��B
     * @tparam T �擾����GameObject�̌^
     * @return GameObject�̃x�N�^�[
     */
    template <typename T>
    std::vector<T*> GetGameObjects()
    {
        std::vector<T*> objects; // STL�z��

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

    // �I�u�W�F�N�g�f�[�^��CSV�`���ŕۑ�����֐�
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
            
            outputFile << "," << obj->GetPosition().x << "," << obj->GetPosition().y << "," << obj->GetPosition().z << ","
                << obj->GetScale().x << "," << obj->GetScale().y << "," << obj->GetScale().z << ","
                << obj->GetRotation().x << "," << obj->GetRotation().y << "," << obj->GetRotation().z << "\n";
        }                                         

        outputFile.close();
    }

    // CSV�`���̃f�[�^����I�u�W�F�N�g�f�[�^��ǂݍ��ފ֐�
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
            if (typeid(*obj) != typeid(Player)) // �^�𒲂ׂ�
            {
                obj->SetDestroy();
            }            
        }

        //�w�b�_���̂Ă�
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

            // �J���}��؂�Ńf�[�^���擾
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

            switch (tag
)
            {
            case BOX:
            {
                BoxObject* box = AddGameObject<BoxObject>(Layer1);
                box->SetPosition(pos);
                box->SetScale(scale);
                box->SetRotation(rot);
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
