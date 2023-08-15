#pragma once
#include "gameObject.h"

//上に乗ると跳ねるオブジェクト
class Trampoline :  public GameObject
{
public:
	void Init() override;
	void Update()override;

	void SetPower(float _power);

	//跳ねる
	void Action(GameObject* obj);
private:
	//跳ねる強さ
	float power = 300.0f;
};

