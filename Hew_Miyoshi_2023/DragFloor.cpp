#include "DragFloor.h"
#include"shader.h"
#include"modelRenderer.h"

void DragFloor::Init()
{
	AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\PS_RGBSplit.cso");
	AddComponent<ModelRenderer>()->Load("asset\\model\\box.obj");
}
