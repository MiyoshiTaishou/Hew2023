/**
 * @file ファイル名.h
 * @brief ジャンプできるようにするコンポーネント
 * @author 三好大翔
 */
#pragma once
#include "component.h"
#include<SimpleMath.h>

//!前方宣言
class GameObject;

class JumpComponent :  public Component
{
public:
	using Component::Component;

	void Update();
	void Draw()override;

private:

	//!重力加速度
	float accGravity = 20.0f;

	//!時間
	float time = 0;

	//!ジャンプの強さ
	float jumpPower = 20.0f;

	//!ジャンプできるか
	bool jumpCheck = true;
};

