#include "main.h"
#include "manager.h"
//#include "input.h"
#include "scene.h"
#include "modelRenderer.h"
#include "sky.h"
#include "camera.h"
#include "shader.h"

#include"ImGuiManager.h"

using namespace DirectX::SimpleMath;

void Sky::Init()
{
	m_Scale = Vector3(100.0f, 100.0f, 100.0f);


	//AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso", "shader\\PS_PolarCoordinates.cso");
	//AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso", "shader\\PS_OrangeScale.cso");
	//AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso", "shader\\PS_BloomBlur.cso");
	AddComponent<Shader>()->Load("shader\\VS_Rotation.cso", "shader\\PS_BloomBlur.cso");
	//AddComponent<Shader>()->Load("shader\\VS_Scale.cso", "shader\\PS_Circle.cso");
	AddComponent<ModelRenderer>()->Load("asset\\model\\sky.obj");

	bloom.bloom = 1.0f;
	bloom.power = 5.0f;
	Renderer::SetBloom(bloom);	
}


void Sky::Update()
{

	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();

	Vector3 cameraPosition = camera->GetPosition();
	m_Position = cameraPosition;

	rot.rotationAngle.x+=0.0005f;

	if (rot.rotationAngle.x > 90.0f)
		rot.rotationAngle .x= 0.0f;

	Renderer::SetRotationAngle(rot);
}

void Sky::Draw()
{
	ImGui::Begin("Sky Bloom");
	ImGui::SliderFloat("power", &bloom.power, 0.0f, 5.0f);
	ImGui::SliderFloat("bloom", &bloom.bloom, 0.0f, 1.0f);
	ImGui::End();

	Renderer::SetBloom(bloom);
}


