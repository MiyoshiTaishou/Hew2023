#pragma once
#include"component.h"
#include<SimpleMath.h>

//当たり判定の親クラス
class Collider : public Component
{
public:

	void Init();

	void Update();

	void SetColliderScale(DirectX::SimpleMath::Vector3 _scale);

private:

	using Component::Component;

protected:
	//当たり判定を見えるようにする
	bool m_View = true;

	//当たり判定の座標
	DirectX::SimpleMath::Vector3 m_ColliderPos;

	//当たり判定の大きさ
	DirectX::SimpleMath::Vector3 m_ColliderScale;

	//当たり判定の回転
	DirectX::SimpleMath::Vector3 m_ColliderRot;
};
