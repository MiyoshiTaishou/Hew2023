#pragma once
#include"gameObject.h"
#include"../Component/animationModel.h"

//指定数集めたらゴール
class Customer : public GameObject
{
private:

	class AnimationModel* m_Model;
	int m_Frame;
	float m_BlendRate;
	//たこ焼きの要求数
	int m_Requests = 8;
	
public:

	void Init() override;
	void Update() override;
	void PreDraw() override;

	void SetRequests(int _count) { m_Requests = _count; }
	int GetRequests() { return m_Requests; }
};