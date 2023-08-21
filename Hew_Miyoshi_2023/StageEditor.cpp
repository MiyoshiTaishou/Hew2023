#include "StageEditor.h"
#include "ImGuiManager.h"
#include "gameObject.h"
#include "box.h"
#include "sky.h"
#include "Player.h"
#include "field.h"
#include "camera.h"

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
