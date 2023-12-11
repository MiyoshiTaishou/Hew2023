#include "Timer.h"
#include<SimpleMath.h>

//コンポーネント
#include "../Component/shader.h"
#include"../Component/sprite.h"

//シーン
#include"../Scene/scene.h"
#include"../Scene/Transition.h"

//システム
#include"../Sysytem/manager.h"

using namespace DirectX::SimpleMath;

void Timer::Init()
{
	AddComponent<Shader>()->Load("../shader\\unlitTextureVS.cso", "../shader\\PS_PolarCoordinates.cso");
	AddComponent<Sprite>()->Init(600,0,100,100,"../asset\\texture\\field.jpg");

	//UI設定
	pollar.baseColor = { 0.0f,0.0f,0.0f,1.0f };//ベースカラー
	pollar.diffColor = { 0.2f,0.2f,0.2f,1.0f };
	pollar.lostColor = { 0.0f,-1.0f,0.0f,1.0f };
	pollar.outer = 0.5f;
	pollar.inner = 0.15f;
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
	Transition* fade = scene->GetGameObject<Transition>();

	if (fade->GetState() == Transition::State::Stop)
	{
		//ゲージ進行
		time += 0.001;

		pollar.gauge1 = 1.0f - ((int)fmod(time, 7.0f) + 1) / 7.0f;
		pollar.gauge2 = 1.0f - fmodf(time, 7.0f) / 7.0f;

		if (pollar.gauge2 < 0.01f)
			fade->FadeOut();

		Renderer::SetPollar(pollar);
	}	
}
