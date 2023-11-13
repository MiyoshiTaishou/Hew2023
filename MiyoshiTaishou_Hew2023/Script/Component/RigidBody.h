#pragma once
#include"component.h"
#include<SimpleMath.h>

//UnityのRigidBodyになるべく近い形を目指す

// どの計算式を使うか
enum class ForceMode
{
	Force,           ///< 質量に依存し、継続的な力を与える
	Acceleration,    ///< 質量に依存せず、継続的な力を与える
	Impulse,         ///< 質量に依存し、瞬間的な力を与える
	VelocityChange   ///< 質量に依存せず、瞬間的な力を与える
};

//どこを固定にするか送る時に使う
enum FrizeNum
{
	Xpos,  ///< X座標の位置を固定
	YPos,  ///< Y座標の位置を固定
	ZPos,  ///< Z座標の位置を固定
	XRot,  ///< X軸の回転を固定
	YRot,  ///< Y軸の回転を固定
	ZRot   ///< Z軸の回転を固定
};

struct Frieze
{
	bool Xpos;  ///< X座標の位置を固定
	bool YPos;  ///< Y座標の位置を固定
	bool ZPos;  ///< Z座標の位置を固定
	bool XRot;  ///< X軸の回転を固定
	bool YRot;  ///< Y軸の回転を固定
	bool ZRot;  ///< Z軸の回転を固定
};

class RigidBody : public Component
{
public:

	void Init();
	void Update();
	void Draw();

	//力を加える
	//引数　力のベクトル,力の計算モード
	void AddForce(DirectX::SimpleMath::Vector3 _force, ForceMode forceMode);

	//軸の固定
	void SetFreeze(FrizeNum freez, bool _b);

	//回転を加える
	void AddTorque(DirectX::SimpleMath::Vector3 _torque, ForceMode forceMode);

	//慣性テンソルの設定
	void SetInetiaTensorOfSpherAngular(float _radius, DirectX::SimpleMath::Vector3 _centerOfMass);

	//直方体のテンソルの設定
	void SetInetiaTensorOfRectangular(float x, float y, float z, DirectX::SimpleMath::Vector3 _centerOfMass);

	//一点に力を加える
	void AddForceToPoint(DirectX::SimpleMath::Vector3 _force, DirectX::SimpleMath::Vector3 localPos, ForceMode forceMode);

private:

	Component::Component;

	//力
	
	//物体の質量
	float m_Mass = 1.0f;			

	//力によって動く際の空気抵抗の大きさ
	float m_Drag = -1.0f;				

	//重力の影響を受ける
	bool m_UseGravity = true;		

	//重力の強さ
	float m_GravityScale = 0.1f;   

	//オブジェクトの現在の速度
	DirectX::SimpleMath::Vector3 m_Velocity; 

	//オブジェクトに現在加えられている力
	DirectX::SimpleMath::Vector3 m_Force;



	//回転

	//オブジェクトの重心の位置(ローカル座標)
	DirectX::SimpleMath::Vector3 m_CenterOfMass;	
	
	//現在の角速度
	DirectX::SimpleMath::Vector3 m_AngularVelocity;

	//現在のトルク
	DirectX::SimpleMath::Vector3 m_Torque;
	
	//慣性テンソル
	DirectX::SimpleMath::Matrix m_InetiaTensor;
	 
	
	//トルクによって回転する際に、オブジェクトに影響する空気抵抗の大きさ
	float m_AngularDrag = -1.0f;

	//固定情報
	Frieze m_Frize;


};
