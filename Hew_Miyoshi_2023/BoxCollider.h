#pragma once
#include"component.h"
#include<SimpleMath.h>


//四角形の当たり判定のコンポーネント
class BoxCollider : public Component
{
public:
	using Component::Component;

	void Init()override;
	void Update()override;
	void Draw()override;

	bool HitCheck(BoxCollider other);

	DirectX::SimpleMath::Vector3 GetHitBox();
	DirectX::SimpleMath::Vector3 GetScale();

private:

	//当たり判定の座標
	DirectX::SimpleMath::Vector3 mHitBox = { 0,0,0 };

	//コライダーのサイズ
	DirectX::SimpleMath::Vector3 mScale = { 1.0f,1.0f,1.0f };	
};

