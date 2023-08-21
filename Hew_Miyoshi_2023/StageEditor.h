#pragma once
#include "scene.h"

struct InfoObjData
{
	DirectX::SimpleMath::Vector3 pos;
	DirectX::SimpleMath::Vector3 scale;
	DirectX::SimpleMath::Vector3 rot;
};

class StageEditor : public Scene
{
public:
	void Init()override;
	void Update()override;
	void Draw()override;

private:
	std::vector<InfoObjData> position;
};

