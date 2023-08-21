#include "StageEditor.h"
#include "ImGuiManager.h"
#include "gameObject.h"
#include "box.h"
#include "sky.h"
#include "Player.h"
#include "field.h"
#include "camera.h"

#include <fstream>

using namespace DirectX::SimpleMath;

void StageEditor::Init()
{
    AddGameObject<Sky>(1);
    AddGameObject<Player>(1);
    AddGameObject<Field>(1);

    AddGameObject<Camera>(0);   
}

void StageEditor::Update()
{
}

void StageEditor::Draw()
{
    ImGui::Begin("Stage Editor");

    // 保存ボタン
    if (ImGui::Button("Save Positions"))
    {
        SavepositionToFile("positions.txt");
    }

    // 読み込みボタン
    if (ImGui::Button("Load Positions"))
    {
        LoadpositionToFile("positions.txt");
    }

    // オブジェクト生成
    if (ImGui::Button("Create Object"))
    {
        Box* box = AddGameObject<Box>(3);
        InfoObjData data;
        data.pos = box->GetPosition();
        data.scale = box->GetScale();
        data.rot = box->GetRotation();
        position.push_back(data);
    }

    std::vector<GameObject*> objects;

    // 各オブジェクトごとの座標設定
    for (int i = 0; i < position.size(); i++)    
        if (ImGui::TreeNode(("Object " + std::to_string(i)).c_str()))
        {
            ImGui::SliderFloat("posX", &position[i].pos.x, -100.0f, 100.0f);
            ImGui::SliderFloat("posY", &position[i].pos.y, -100.0f, 100.0f);
            ImGui::SliderFloat("posZ", &position[i].pos.z, -100.0f, 100.0f);

            ImGui::SliderFloat("scaleX", &position[i].scale.x, -100.0f, 100.0f);
            ImGui::SliderFloat("scaleY", &position[i].scale.y, -100.0f, 100.0f);
            ImGui::SliderFloat("scaleZ", &position[i].scale.z, -100.0f, 100.0f);

            ImGui::SliderFloat("rotX", &position[i].rot.x, -100.0f, 100.0f);
            ImGui::SliderFloat("rotY", &position[i].rot.y, -100.0f, 100.0f);
            ImGui::SliderFloat("rotZ", &position[i].rot.z, -100.0f, 100.0f);

            ImGui::TreePop();
        }    

    // 座標代入
    int iterat = 0;
    for (auto& objectList : m_GameObject)    
        for (GameObject* object : objectList)        
            if (iterat < position.size() && typeid(*object) == typeid(Box))
            {
                object->SetPosition(position[iterat].pos);
                object->SetScale(position[iterat].scale);
                object->SetRotation(position[iterat].rot);
                iterat++;
            }            

    ImGui::End();
}

void StageEditor::SavepositionToFile(const std::string& filename)
{
    std::ofstream outputFile(filename);
    
    if (outputFile.is_open())
    {
        for (const InfoObjData& position : position)
        {
            outputFile << position.pos.x << " " << position.pos.y << " " << position.pos.z << " "
                << position.scale.x << " " << position.scale.y << " " << position.scale.z << " "
                << position.rot.x << " " << position.rot.y << " " << position.rot.z << "\n";
        }

        outputFile.close();
    }
    else
    {
        // エラーメッセージを表示またはログに記録
    }
}

void StageEditor::LoadpositionToFile(const std::string& filename)
{
    std::ifstream inputFile(filename);

    if (inputFile.is_open())
    {
        position.clear();

        InfoObjData data;
        while (inputFile >> data.pos.x >> data.pos.y >> data.pos.z
            >> data.scale.x >> data.scale.y >> data.scale.z
            >> data.rot.x >> data.rot.y >> data.rot.z)
        {
            Box* box = AddGameObject<Box>(3);
            position.push_back(data);
        }

        inputFile.close();
    }
    else
    {
        // エラーメッセージを表示またはログに記録
    }
}
