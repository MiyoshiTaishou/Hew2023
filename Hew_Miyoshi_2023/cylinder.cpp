#include "main.h"
#include "manager.h"
#include "renderer.h"
//#include "input.h"
//#include "scene.h"
#include "modelRenderer.h"
#include "cylinder.h"
//#include "shadow.h"
#include "shader.h"
#include"BoxCollider.h"


void Cylinder::Init()
{
	AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\PS_RGBSplit.cso");
	AddComponent<ModelRenderer>()->Load("asset\\model\\cylinder.obj");
}