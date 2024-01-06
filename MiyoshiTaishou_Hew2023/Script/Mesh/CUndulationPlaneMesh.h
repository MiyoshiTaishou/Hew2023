#pragma once
#include	<random>
#include	"CPlaneMesh.h"
#include	"CPlaneMeshTexture.h"

class CUndulationPlaneMesh : public CPlaneMesh {
public:
	void MakeUndulation(float min, float max);
	void MakeUndulationPerlinnoise(float max, double octave, double persistence);
	void MakeUndulationSelf();
	void SaveUndulation(const std::string& filename);
	void LoadUndulation(const std::string& filename);
};
