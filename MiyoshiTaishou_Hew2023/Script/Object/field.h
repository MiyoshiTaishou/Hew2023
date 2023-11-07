#pragma once
#include	<d3d11.h>
#include	<SimpleMath.h>
#include	"gameObject.h"


//前方宣言
class CPlane;
class Collider;

//ステージのフィールド
class Field : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	//std::vector<CPlane> m_Planes;

	//当たり判定コンポーネント
	Collider* m_Collider;

public:
	void Init();
	void Uninit();	
	void Draw();

	void makepalenequatation();

	// 現在位置の高さを求める
	float  GetFieldHeight(DirectX::SimpleMath::Vector3 pos);
};