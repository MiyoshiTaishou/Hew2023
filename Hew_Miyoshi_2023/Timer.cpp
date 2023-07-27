#include "Timer.h"
#include "shader.h"
#include<SimpleMath.h>
#include"sprite.h"
#include"scene.h"
#include"manager.h"
#include"Goal.h"

using namespace DirectX::SimpleMath;

void Timer::Init()
{
	AddComponent<Shader>()->Load("shader\\unlitTextureVS.cso", "shader\\PS_PolarCoordinates.cso");
	AddComponent<Sprite>()->Init(0,0,200,200,"asset\\texture\\field.jpg");

	//UI設定
	pollar.baseColor = { 0.0f,0.0f,0.0f,1.0f };//ベースカラー
	pollar.diffColor = { 0.2f,0.2f,0.2f,1.0f };
	pollar.lostColor = { 0.0f,-1.0f,0.0f,1.0f };
	pollar.outer = 1.0f;
	pollar.inner = 0.3f;
	pollar.gauge1 = 1.0f - ((int)fmod(time, 7.0f) + 1) / 7.0f;
	pollar.gauge2 = 1.0f - fmodf(time, 7.0f) / 7.0f;

	Renderer::SetPollar(pollar);
}

void Timer::Uninit()
{	
}

void Timer::Draw()
{

}

void Timer::Update()
{	
	Scene* scene = Manager::GetScene();
	Goal* goal = scene->GetGameObject<Goal>();

	if (goal)
	{
		//ゲージ進行
		time += 0.1;

		pollar.gauge1 = 1.0f - ((int)fmod(time, 7.0f) + 1) / 7.0f;
		pollar.gauge2 = 1.0f - fmodf(time, 7.0f) / 7.0f;

		if (pollar.gauge2 < 0.01f)
			if (goal)
				goal->SetDestroy();

		Renderer::SetPollar(pollar);
	}
}
