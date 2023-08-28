#pragma once
#include "scene.h"
#include "StageEditor.h"

class Game :  public Scene
{
private:
	class Transition* m_Transition{};
	class FadeUI* m_Fade{};
	bool m_Goal = false;
public:
	void Init()override;		
	void Update()override;
	void LoadpositionToFile(const std::string& filename);
};

