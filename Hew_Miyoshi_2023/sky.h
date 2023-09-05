#pragma once

#include "gameObject.h"
#include "renderer.h"

//背景オブジェクト
class Sky : public GameObject
{

private:

	//シェーダーの値をいじれるようにするための変数
	Bloom bloom;
	RotationAngle rot;

public:
	void Init() override;
	void Update() override;
	void Draw()override;
};