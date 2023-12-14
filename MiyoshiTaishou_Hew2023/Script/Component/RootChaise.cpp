#include "RootChaise.h"
#include"../ImGui/ImGuiManager.h"
#include"../Object/gameObject.h"

using namespace DirectX::SimpleMath;

void RootChaise::Init()
{
    for (int i = 0; i < MAX_BEJIE; i++)
    {
        //球のメッシュ追加  
        m_Sphere[i] = new CSphereMesh();
        m_Sphere[i]->Init(2.0f, Color(1, 1, 1, 1), 100, 100);

        m_MeshRenderer[i] = new CMeshRenderer();
        m_MeshRenderer[i]->Init(*m_Sphere[i]);

        m_SpherePos[i].x = i * 10;
    }   
}

void RootChaise::Uninit()
{
    for (int i = 0; i < MAX_BEJIE; i++)
    {
        delete m_Sphere[i];
        m_Sphere[i] = nullptr;

        delete m_MeshRenderer[i];
        m_MeshRenderer[i] = nullptr;
    }    
}

void RootChaise::Draw()
{
    for (int i = 0; i < MAX_BEJIE; i++)
    {
        // ワールド変換行列生成
        // マトリクス設定
        Matrix world, scale, trans;
        scale = DirectX::SimpleMath::Matrix::CreateScale(Vector3(1.0f, 1.0f, 1.0f));
        trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_SpherePos[i].x, m_SpherePos[i].y, m_SpherePos[i].z);
        world = scale * trans;

        // GPUに行列をセットする
        Renderer::SetWorldMatrix(&world);//位置
       
        m_MeshRenderer[i]->Draw();
    }   

    ImGui::Begin("Collider");
    for (int i = 0; i < 4; i++)
    {
        ImGui::SliderFloat("PosX" + i, &m_SpherePos[i].x, -100, 100);
        ImGui::SliderFloat("PosY" + i, &m_SpherePos[i].y, -100, 100);
        ImGui::SliderFloat("PosZ" + i, &m_SpherePos[i].z, -100, 100);
    }    
    ImGui::End();

}

void RootChaise::Update()
{
    m_Rate += m_MoveSpeed;

    float move;
    move = (-2 * (m_Rate * m_Rate * m_Rate)) + (3 * (m_Rate * m_Rate));
    //move = (-1 * (m_Rate * m_Rate)) + (2 * m_Rate);
    if (m_Rate > 1.0f)
    {
        m_Rate = 0.0f;
    }

    //開始位置から[2]の位置までのlerp
    m_SpherePos[4] = Vector3::Lerp(m_SpherePos[0], m_SpherePos[1], move);    
    m_SpherePos[5] = Vector3::Lerp(m_SpherePos[1], m_SpherePos[2], move);    
    m_SpherePos[6] = Vector3::Lerp(m_SpherePos[4], m_SpherePos[5], move);    

    m_GameObject->SetPosition(m_SpherePos[6]);
}
