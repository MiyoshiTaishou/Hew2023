#pragma once

#include "gameObject.h"
#include "renderer.h"

class Sky : public GameObject
{

private:
	Bloom bloom;

public:
	void Init() override;
	void Update() override;
	void Draw()override;
};