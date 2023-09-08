/**
 * @file �t�@�C����.h
 * @brief �W�����v�ł���悤�ɂ���R���|�[�l���g
 * @author �O�D����
 */
#pragma once
#include "component.h"
#include<SimpleMath.h>

//!�O���錾
class GameObject;

class JumpComponent :  public Component
{
public:
	using Component::Component;

	void Update();
	void Draw()override;

private:

	//!�d�͉����x
	float accGravity = 20.0f;

	//!����
	float time = 0;

	//!�W�����v�̋���
	float jumpPower = 20.0f;

	//!�W�����v�ł��邩
	bool jumpCheck = true;
};

