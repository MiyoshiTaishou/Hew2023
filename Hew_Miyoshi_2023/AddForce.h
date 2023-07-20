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

class Rigidbody : public Component
{
public:
	using Component::Component;
	
	void Init(float _mass, float _drag);
	void Update() override;

	void AddForce(DirectX::SimpleMath::Vector3 _force, ForceMode forceMode);	
private:
	float mass;//オブジェクトの質量
	float drag;//摩擦
	DirectX::SimpleMath::Vector3 velocity;//オブジェクトの現在の速度
	DirectX::SimpleMath::Vector3 force;//オブジェクトに現在加えられている力
};

