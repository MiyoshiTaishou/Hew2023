#pragma once
#include"gameObject.h"

class Audio;

//くっつけれるオブジェクトはこのクラスを継承する
class StickObject : public GameObject
{
public:

	void Init();
	void Update();

	//くっついたときに呼ぶ処理
	void Stick(DirectX::SimpleMath::Vector3 _pos);

private:	

	//元のサイズからどれだけ小さくするかの倍率
	float m_ScaleDown = 0.1f;

	Audio* m_HitSE;

protected:
	//くっついているかどうか
	bool m_Stick = false;
};
