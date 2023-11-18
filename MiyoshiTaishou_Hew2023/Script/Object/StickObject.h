#pragma once
#include"gameObject.h"


//くっつけれるオブジェクトはこのクラスを継承する
class StickObject : public GameObject
{
public:
	
	void Update();

	//くっついたときに呼ぶ処理
	void Stick(DirectX::SimpleMath::Vector3 _pos);

private:

	//くっついているかどうか
	bool m_Stick = false;

	//元のサイズからどれだけ小さくするかの倍率
	float m_ScaleDown = 0.1f;
};
