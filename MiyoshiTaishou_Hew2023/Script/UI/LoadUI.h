#pragma once


#include "../Object/gameObject.h"

class Audio;

class LoadUI : public GameObject
{
private:

	//lerp処理が完了したか
	bool m_Goal = true;

	//0~1でlerpの進行を管理
	float m_Rate = 0;
	
	//初期位置
	DirectX::SimpleMath::Vector3 m_StratPos;

	//中間地点
	DirectX::SimpleMath::Vector3 m_IntermediatePos;

	//目的地
	DirectX::SimpleMath::Vector3 m_GoalPos;

public:
	void Init();		
	void Update();
	//ロード中にする処理
	void LoadAction(Audio* _audio);
};