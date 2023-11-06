#pragma once
#include"gameObject.h"

enum PLAYERSTATE
{
	IDLE,
	HIT,
	NONE,
};

class Player : public GameObject
{
public:

	void Init();
	void Update();
	void Draw();

	//当たり判定処理
	void Collision();

	//コントローラー入力
	void ConInput();

private:

	PLAYERSTATE state = IDLE;
};
