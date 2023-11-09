#pragma once
#include	<random>
#include	"CPlaneMesh.h"
#include	"CPlaneMeshTexture.h"

class CUndulationPlaneMesh : public CPlaneMeshTexture {
public:
	void MakeUndulation(float min, float max);
};
