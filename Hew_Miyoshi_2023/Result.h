#pragma once
#include "scene.h"
class Result : public Scene
{
private:
	class Transition* m_Transition{};
	class FadeUI* m_Fade{};
public:
	void Init()override;
	void Update()override;
};

