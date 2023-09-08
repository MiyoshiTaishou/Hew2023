#pragma once
#include<SimpleMath.h>
#include "component.h"

//物理挙動コンポーネント

// どの計算式を使うか
enum class ForceMode
{
	Force,           ///< 質量に依存し、継続的な力を与える
	Acceleration,    ///< 質量に依存せず、継続的な力を与える
	Impulse,         ///< 質量に依存し、瞬間的な力を与える
	VelocityChange   ///< 質量に依存せず、瞬間的な力を与える
};

// 固定にする箇所
enum class Freeze
{
	Xpos,  ///< X座標の位置を固定
	YPos,  ///< Y座標の位置を固定
	ZPos,  ///< Z座標の位置を固定
	XRot,  ///< X軸の回転を固定
	YRot,  ///< Y軸の回転を固定
	ZRot   ///< Z軸の回転を固定
};

/**
 * @brief 物理挙動コンポーネント
 */
class Rigidbody : public Component
{
public:
    using Component::Component;

    /**
     * @brief コンポーネントの初期化
     * @param _mass 質量
     * @param _drag 摩擦
     * @param _gravityScale 重力の強さ
     */
    void Init(float _mass, float _drag, float _gravityScale);

    /**
     * @brief コンポーネントの更新
     */
    void Update() override;

    /**
     * @brief コンポーネントの描画
     */
    void Draw() override;

    /**
     * @brief 力を加える
     * @param _force 力のベクトル
     * @param forceMode 力の計算モード
     */
    void AddForce(DirectX::SimpleMath::Vector3 _force, ForceMode forceMode);

    /**
     * @brief 現在の速度を取得
     * @return 速度のベクトル
     */
    DirectX::SimpleMath::Vector3 GetVelocity();

    /**
     * @brief 速度を設定
     * @param _vel 速度のベクトル
     */
    void SetVelocity(DirectX::SimpleMath::Vector3 _vel);

    /**
     * @brief 力を設定
     * @param _force 力のベクトル
     */
    void SetForce(DirectX::SimpleMath::Vector3 _force);

    /**
     * @brief 特定の軸の固定を設定
     * @param freez 固定する軸
     * @param _b trueなら固定、falseなら固定解除
     */
    void SetFreeze(Freeze freez, bool _b);

    /**
     * @brief 特定の軸が固定されているか取得
     * @param freez 軸
     * @return trueなら固定、falseなら固定されていない
     */
    bool GetFreeze(Freeze freez);

    /**
     * @brief 摩擦係数を設定
     * @param _drag 摩擦係数
     */
    void SetDrag(float _drag);

    /**
     * @brief 摩擦係数を初期化
     */
    void InitDrag();

private:
    float mass;                       ///< オブジェクトの質量
    float drag;                       ///< 摩擦係数
    float saveDrag;                   ///< 摩擦係数の保存用
    float gravityScale;               ///< 重力の強さ
    DirectX::SimpleMath::Vector3 velocity; ///< オブジェクトの現在の速度
    DirectX::SimpleMath::Vector3 force;    ///< オブジェクトに現在加えられている力

    bool mXPos = false;   ///< X軸の位置を固定するか
    bool mYPos = false;   ///< Y軸の位置を固定するか
    bool mZPos = false;   ///< Z軸の位置を固定するか
    bool mXRot = false;   ///< X軸の回転を固定するか
    bool mYRot = false;   ///< Y軸の回転を固定するか
    bool mZRot = false;   ///< Z軸の回転を固定するか
};