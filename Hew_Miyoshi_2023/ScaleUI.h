#pragma once
#include"renderer.h"
#include "gameObject.h"

class ScaleUI :
    public GameObject
{
public:
    void Init();
    void Update();
	void Draw();

private:
	ScaleShader scaleShader;
	float time = 0.0f;
	
	class Sprite* m_Sprite{};
};

