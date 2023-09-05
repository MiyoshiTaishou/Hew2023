#pragma once
#include<SimpleMath.h>
#include "component.h"

//アッドフォース
enum class ForceMode
{
	Force, // 質量に依存し、継続的な力を与える
	Acceleration, // 質量に依存せず、継続的な力を与える
	Impuluse, // 質量に依存し、瞬間的な力を与える
	VelocityChange // 質量に依存せず、瞬間的な力を与える
};

enum class Freeze
{
	Xpos,
	YPos,
	ZPos,
	XRot,
	YRot,
	ZRot
};

class Rigidbody : public Component
{
public:
	using Component::Component;
	
	void Init(float _mass, float _drag,float _gravityScale);
	void Update() override;
	void Draw() override;

	void AddForce(DirectX::SimpleMath::Vector3 _force, ForceMode forceMode);	

	DirectX::SimpleMath::Vector3 GetVelocity();
	void SetVelocity(DirectX::SimpleMath::Vector3 _vel);

	void SetForce(DirectX::SimpleMath::Vector3 _force);

	void SetFreeze(Freeze freez,bool _b);
	bool GetFreeze(Freeze freez);

	void SetDrag(float _drag);
	void InitDrag();

private:
	float mass;//オブジェクトの質量
	float drag;//摩擦
	float saveDrag;//保存用
	float gravityScale;//重力の強さ
	DirectX::SimpleMath::Vector3 velocity;//オブジェクトの現在の速度
	DirectX::SimpleMath::Vector3 force;//オブジェクトに現在加えられている力	
	
	bool mXPos = false;
	bool mYPos = false;
	bool mZPos = false;
	bool mXRot = false;
	bool mYRot = false;
	bool mZRot = false;
};

