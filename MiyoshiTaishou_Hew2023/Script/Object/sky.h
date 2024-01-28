#pragma once

#include "gameObject.h"
#include "../Render/renderer.h"

//背景オブジェクト
class Sky : public GameObject
{

private:

	//シェーダーの値をいじれるようにするための変数
	Bloom bloom;
	RotationAngle rot;

public:
	void Init() override;
	void Init(const char* _name);
	void Update() override;
	void Draw()override;
};