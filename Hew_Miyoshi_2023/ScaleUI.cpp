#include "ScaleUI.h"
#include"shader.h"
#include"sprite.h"
#include"ImGuiManager.h"

void ScaleUI::Init()
{
	AddComponent<Shader>()->Load("shader\\VS_Scale.cso", "shader\\PS_Circle.cso");
	AddComponent<Sprite>()->Init(0, 0, 10, 10, "asset\\texture\\field.jpg");

	scaleShader.circlePosition = { 0.0f,0.8f };
	scaleShader.circleRadius = 0.01f;
	scaleShader.screenSize = { 1.0f,1.0f };
}

void ScaleUI::Update()
{	
	
	scaleShader.circlePosition.x += 0.001f;
	scaleShader.circlePosition.y -= 0.001f;
	scaleShader.circleRadius += 0.001f;
	Renderer::SetScaleShader(scaleShader);	
}

void ScaleUI::Draw()
{
	ImGui::Begin("Scale");
	ImGui::SliderFloat("radius", &scaleShader.circleRadius, 0.0f, 0.1f);
	ImGui::SliderFloat("positionX", &scaleShader.circlePosition.x, 0.0f, 1.0f);
	ImGui::SliderFloat("positionY", &scaleShader.circlePosition.y, 0.0f, 1.0f);
	ImGui::SliderFloat("sizeX", &scaleShader.screenSize.x, 0.0f, 1.0f);
	ImGui::SliderFloat("sizeY", &scaleShader.screenSize.y, 0.0f, 1.0f);
	ImGui::End();

	Renderer::SetScaleShader(scaleShader);
}
