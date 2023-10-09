#include "Octopus.h"
#include"shader.h"
#include"modelRenderer.h"

void Octopus::Init()
{
	AddComponent<Shader>()->Load("shader\\vertexLightingVS.cso", "shader\\vertexLightingPS.cso");
	AddComponent<ModelRenderer>()->Load("asset\\model\\Octopus.obj");

	m_Position.z = 20.0f;
	m_Position.y = 3.0f;
	m_Scale *= 3.0f;
}
