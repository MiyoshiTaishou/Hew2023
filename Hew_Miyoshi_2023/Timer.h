#pragma once
#include "gameObject.h"
#include"renderer.h"

//ステージの制限時間表示
class Timer : public GameObject
{
public:
	void Init();
	void Uninit();
	void Draw();
	void Update();
private:
	Pollar pollar;
	float time = 0.0f;	
};

