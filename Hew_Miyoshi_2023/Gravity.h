#pragma once
#include "component.h"
#include<SimpleMath.h>

//前方宣言
class GameObject;

//重力をつけるコンポーネント
class Gravity : public Component
{
public:

	using Component::Component;

	void Update();

private:

	//重力の強さ
	DirectX::SimpleMath::Vector3 gravityPower = { 0,1,0 };

	//重力加速度
	float accGravity = 0.0098f;

	//時間
	int time = 0;
};

