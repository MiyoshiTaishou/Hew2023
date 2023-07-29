#include "PostProcess.h"
#include"shader.h"
#include"sprite.h"

void PostProcess::Init()
{
	AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso", "shader\\PS_ConcentrationShader.cso");
	AddComponent<Sprite>()->Init(0, 0, 1280, 720, "asset\\texture\\field.jpg");
}
