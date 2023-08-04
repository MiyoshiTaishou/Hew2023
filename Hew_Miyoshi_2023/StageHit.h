#pragma once

#include<SimpleMath.h>
#include<vector>

class GameObject;

// �n�`�f�[�^�̖ʂ̕��������
struct PLANEINFO {
	DirectX::SimpleMath::Plane		plane;				//���ʂ̕�����
	DirectX::SimpleMath::Vector3	p0, p1, p2;		//���_���W
};

void StageHitInit(GameObject* obj, const char* FileName);
void StageHitExit();
void CreateStagePlaneInfoAll(std::vector<DirectX::SimpleMath::Vector3>& v, int idx);
bool SearchAllSurface(float x, float z, DirectX::SimpleMath::Vector3& ans);
void CreatePlaneInfo(const DirectX::SimpleMath::Vector3& p1, const DirectX::SimpleMath::Vector3& p2, const DirectX::SimpleMath::Vector3& p3, DirectX::SimpleMath::Plane& plane);
bool LinetoPlaneCross(const DirectX::SimpleMath::Plane& plane, const DirectX::SimpleMath::Vector3& p0, const DirectX::SimpleMath::Vector3& wv, DirectX::SimpleMath::Vector3 ans);
bool CheckInTriangle(const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b, const DirectX::SimpleMath::Vector3& c, const DirectX::SimpleMath::Vector3& p);
