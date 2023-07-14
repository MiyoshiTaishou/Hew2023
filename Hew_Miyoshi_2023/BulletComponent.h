#pragma once
#include "component.h"
#include<SimpleMath.h>

//弾を発射する溜めのコンポーネント
class BulletComponent : public Component
{
public:
	using Component::Component;
	
	void Update();
	void Shot(DirectX::SimpleMath::Vector3 vec,GameObject &obj,DirectX::SimpleMath::Vector3 pos);
private:

	//飛ばす方向
	DirectX::SimpleMath::Vector3 shotVec;

	//発射したか
	bool bShot = false;

	//時間変数
	float time = 0.0f;

	//速度
	float speed = 10.0f;
};

