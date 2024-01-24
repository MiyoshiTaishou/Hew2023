#pragma once

#include"../Object/gameObject.h"

//UIの状態を管理する
enum STATEUI
{
	Stop,   //処理開始前
	AddRun,	//加算処理中
	SubRun, //減算処理中
};

class Sprite;

class HitUI : public GameObject
{
public:

	void Init();
	void Init(int x, int y, int Width, int Height, const char* TextureName);
	void Update();
	void Draw();
	//UI表示
	void Indication();

private:

	MATERIAL m_MT;
	STATEUI m_State = Stop;
	Sprite* m_Sprite;
	DirectX::SimpleMath::Color m_Color;	

	//計測時間
	float m_Time = 0.0f;

	//時間に足す値この値で上がり方を調整
	float m_AddTime = 0.005f;
};