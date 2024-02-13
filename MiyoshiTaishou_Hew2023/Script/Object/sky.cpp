#include "../Sysytem/main.h"
#include "../Sysytem/manager.h"
//#include "input.h"
#include "../Scene/scene.h"
#include "../Render/modelRenderer.h"
#include "sky.h"
#include "camera.h"
#include "../Component/shader.h"

#include"../ImGui/ImGuiManager.h"

using namespace DirectX::SimpleMath;

void Sky::Init()
{
	m_Scale = Vector3(1000.0f, 1000.0f, 1000.0f);
	
	AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso", "../shader\\PS_BloomBlur.cso");
	
	AddComponent<ModelRenderer>()->Load("../asset\\model\\sky.obj");

	bloom.bloom = 1.0f;
	bloom.power = 5.0f;
	Renderer::SetBloom(bloom);	
}

void Sky::Init(const char* _name)
{
	m_Scale = Vector3(1000.0f, 1000.0f, 1000.0f);	
	AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso", "../shader\\PS_BloomBlur.cso");
	AddComponent<ModelRenderer>()->Load(_name);

	bloom.bloom = 1.0f;
	bloom.power = 5.0f;
	Renderer::SetBloom(bloom);
}


void Sky::Update()
{
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();

	//ƒJƒƒ‰‚ª‘¶Ý‚·‚é‚È‚ç
	if (camera)
	{
		Vector3 cameraPosition = camera->GetPosition();
		m_Position = cameraPosition;
	}

	rot.rotationAngle.x += 0.0005f;

	if (rot.rotationAngle.x > 90.0f)
		rot.rotationAngle .x= 0.0f;

	Renderer::SetRotationAngle(rot);
}

void Sky::Draw()
{
	Renderer::SetBloom(bloom);
}


