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

	void SetRelative(DirectX::SimpleMath::Vector3 _rel);

	void SetCanHit(bool _hit);
	
	DirectX::SimpleMath::Vector3 GetPos()
	{
		return m_ColliderPos;
	}

	DirectX::SimpleMath::Vector3 GetRelative()
	{
		return m_Relative;
	}

	bool CheckInTriangle(
		const DirectX::SimpleMath::Vector3& a,
		const DirectX::SimpleMath::Vector3& b,
		const DirectX::SimpleMath::Vector3& c,
		const DirectX::SimpleMath::Vector3& p);

	bool LinetoPlaneCross(
		const DirectX::SimpleMath::Plane& plane,		//平面の方程式
		const DirectX::SimpleMath::Vector3& p0,			//直線の起点
		const DirectX::SimpleMath::Vector3& wv,			//直線の方向ベクトル
		float& t,			// 交点位置情報	
		DirectX::SimpleMath::Vector3& ans);		//交点座標

private:

	using Component::Component;

protected:
	//当たり判定を見えるようにする
	bool m_View = true;

	//当たり判定の座標
	DirectX::SimpleMath::Vector3 m_ColliderPos;

	//相対位置
	DirectX::SimpleMath::Vector3 m_Relative;

	//当たり判定の大きさ
	DirectX::SimpleMath::Vector3 m_ColliderScale;

	//当たり判定の回転
	DirectX::SimpleMath::Vector3 m_ColliderRot;

	//当たり判定が有効かどうか
	bool m_CanHit = true;

};
