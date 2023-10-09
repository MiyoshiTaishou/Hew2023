#include "main.h"
#include "manager.h"
#include "renderer.h"
//#include "input.h"
//#include "scene.h"
#include "modelRenderer.h"
#include "box.h"
//#include "shadow.h"
#include "shader.h"
#include"BoxCollider.h"
#include"ImGuiManager.h"

void Box::Init()
{
	//AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");
	AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\PS_RGBSplit.cso");
	//AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\PS_BloomBlur.cso");
	//AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\PS_ConcentrationShader.cso");
	//AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\PS_PolarCoordinates.cso");
	AddComponent<ModelRenderer>()->Load("asset\\model\\box.obj");
	AddComponent<BoxCollider>()->Init();
//	AddComponent<Shadow>()->SetSize(8.0f);
}