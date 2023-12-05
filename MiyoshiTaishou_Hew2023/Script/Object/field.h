#pragma once
#include	<d3d11.h>
#include	<SimpleMath.h>
#include	"gameObject.h"
#include	"../Mesh/CUndulationPlaneMesh.h"
#include	"../Mesh/CMeshRenderer.h"
#include	"../Mesh/CPlane.h"

//前方宣言
class CPlane;
class Collider;

//ステージのフィールド
class Field : public GameObject
{
private:
	CMeshRenderer		m_renderer;						// フィールドのレンダラ

	ID3D11ShaderResourceView* m_Texture{};

	// 平面プレーン
	CUndulationPlaneMesh	m_planemesh;				// 平面メッシュ

	std::vector<CPlane> m_planes;						// 平面の方程式群

	// 平面の方程式を生成する（全面）
	void MakeEquatation();

	Collider* m_Collider;

	float dis = 0.0f;

public:
	void Init();
	void Uninit();	
	void Draw();

	// 現在位置の高さを求める
	float  GetFieldHeight(DirectX::SimpleMath::Vector3 pos);
	//_offRigidBodyの影響を与えるかどうか
	float GetFieldHeightBySqno(DirectX::SimpleMath::Vector3 pos, GameObject& obj);

	void PointPlaneCollision(DirectX::SimpleMath::Vector3 _point);

	// 法線ベクトルから斜めの方向を計算
	DirectX::SimpleMath::Vector3 CalculateDiagonalDirection(DirectX::SimpleMath::Vector3 normal);

	DirectX::SimpleMath::Vector3 direction;
	DirectX::SimpleMath::Vector3 normalDB;	

	// GetMAX XZ
	DirectX::SimpleMath::Vector3 GetMax() {

		DirectX::SimpleMath::Vector3 max;

		max.x = m_planemesh.GetWidth() / 2.0f;
		max.z = m_planemesh.GetHeight() / 2.0f;
		max.y = 0.0f;

		return max;
	}

	// GetMIN XZ
	DirectX::SimpleMath::Vector3 GetMin() {
		DirectX::SimpleMath::Vector3 min;

		min.x = -m_planemesh.GetWidth() / 2.0f;
		min.z = -m_planemesh.GetHeight() / 2.0f;
		min.y = 0.0f;

		return min;
	}
};