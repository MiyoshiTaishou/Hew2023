#pragma once
#include<SimpleMath.h>
#include "component.h"

//OBB用構造体
struct OBBinfo
{
	DirectX::SimpleMath::Vector3 vecAxisX;//X軸
	DirectX::SimpleMath::Vector3 vecAxisY;//Y軸
	DirectX::SimpleMath::Vector3 vecAxisZ;//Z軸
	DirectX::SimpleMath::Vector3 center;//中心座標(ローカル座標系)
	DirectX::SimpleMath::Vector3 currentcenter;//BBOXの現在位置
	float fLengthX;//BBOX Xサイズ
	float fLengthY;//BBOX Yサイズ
	float fLengthZ;//BBOX Zサイズ
};

bool CompareLength(
	const OBBinfo& pboxA,
	const OBBinfo& pboxB,
	const DirectX::SimpleMath::Vector3& pvecSeparate,// 分離軸
	const DirectX::SimpleMath::Vector3& pvecDistance)
{
	float fDistance;
	// 分離軸に射影した中心間を結ぶベクトル
		
	fDistance = pvecDistance.Dot(pvecSeparate);
	// 内積を計算
	fDistance = fabsf(fDistance);	// 絶対値
	
	//分離軸上にボックスAを射影した影の長さ
	float fShadowA = 0;
	//分離軸上にボックスＢを射影した影の長さ
	float fShadowB = 0;
	//ボックスAの”影”を算出
	float fShadowAx;
	float fShadowAy;
	float fShadowAz;
	// X軸を分離軸に射影
	fShadowAx = pvecSeparate.Dot(pboxA.vecAxisX);	
	fShadowAx = fabsf(fShadowAx * (pboxA.fLengthX / 2));
	// Y軸を分離軸に射影
	fShadowAy = pvecSeparate.Dot(pboxA.vecAxisY);
	fShadowAy = fabsf(fShadowAy * (pboxA.fLengthY / 2));
	
	// Z軸を分離軸に射影
	fShadowAz = pvecSeparate.Dot(pboxA.vecAxisZ);
	fShadowAz = fabsf(fShadowAz * (pboxA.fLengthZ / 2));
	
	fShadowA = fShadowAx + fShadowAy + fShadowAz;
	
	//ボックスBの”影”を算出
	float fShadowBx;
	float fShadowBy;
	float fShadowBz;
	
	// X軸を分離軸に射影
	fShadowBx = pvecSeparate.Dot(pboxB.vecAxisX);	
	fShadowBx = fabsf(fShadowBx * (pboxB.fLengthX / 2));
	
	// Y軸を分離軸に射影
	fShadowBy = pvecSeparate.Dot(pboxB.vecAxisY);
	fShadowBy = fabsf(fShadowBy * (pboxB.fLengthY / 2));
	
	// Z軸を分離軸に射影
	fShadowBz = pvecSeparate.Dot(pboxB.vecAxisZ);
	fShadowBz = fabsf(fShadowBz * (pboxB.fLengthZ / 2));
	
	fShadowB = fShadowBx + fShadowBy + fShadowBz;
	
	if (fDistance > fShadowA + fShadowB) {
		return false;
	}
	return true;
}

bool Collisom(OBBinfo& obbA, OBBinfo& obbB)
{
	//分離軸
	DirectX::SimpleMath::Vector3 vecSeparate;

	// 2つのオブジェクトを結んだベクトルを計算
	DirectX::SimpleMath::Vector3 vecDistance;

	DirectX::SimpleMath::Vector3 obbposA = obbA.currentcenter;
	DirectX::SimpleMath::Vector3 obbposB = obbB.currentcenter;

	vecDistance.x = obbposA.x - obbposB.x;
	vecDistance.y = obbposA.y - obbposB.y;
	vecDistance.z = obbposA.z - obbposB.z;

	bool sts;// 戻り値

	// OBB-A軸リスト
	DirectX::SimpleMath::Vector3* OBB_A_Axis[3] = {
		&obbA.vecAxisX,
		&obbA.vecAxisY,
		&obbA.vecAxisZ,
	};

	// OBB-B軸リスト
	DirectX::SimpleMath::Vector3* OBB_B_Axis[3] = {
		&obbB.vecAxisX,
		&obbB.vecAxisY,
		&obbB.vecAxisZ,
	};

	// OBB-Aの３軸を分離軸にしてチェック
	for (int i = 0; i < 3; i++) {
		vecSeparate.x = OBB_A_Axis[i]->x;
		vecSeparate.y = OBB_A_Axis[i]->y;
		vecSeparate.z = OBB_A_Axis[i]->z;

		vecSeparate.Normalize();//正規化

		sts = CompareLength(obbA,// OBB-A
			obbA,// OBB-B
			vecSeparate,// 分離軸
			vecDistance);// ２つのオブジェクトの中心を結ぶベクトル
		if (sts == false) {
			return false;
		}
	}

	// OBB-Bの３軸を分離軸にしてチェック
	for (int i = 0; i < 3; i++) {
		vecSeparate.x = OBB_B_Axis[i]->x;
		vecSeparate.y = OBB_B_Axis[i]->y;
		vecSeparate.z = OBB_B_Axis[i]->z;

		vecSeparate.Normalize();//正規化
		sts = CompareLength(obbA,// OBB-A
			obbA,// OBB-B
			vecSeparate,// 分離軸
			vecDistance);// ２つのオブジェクトの中心を結ぶベクトル
		if (sts == false) {
			return false;
		}
	}

	// 外積を分離軸として計算
	for (int p1 = 0; p1 < 3; p1++) {
		for (int p2 = 0; p2 < 3; p2++) {
			DirectX::SimpleMath::Vector3	crossseparate;// 外積ベクトル

			// 外積を計算する
			crossseparate = OBB_A_Axis[p1]->Cross(*OBB_B_Axis[p2]);

			// 正規化
			crossseparate.Normalize();

			sts = CompareLength(
				obbA,// OBB-A
				obbB,// OBB-B
				crossseparate,// 分離軸
				vecDistance);
			// ２つのオブジェクトを結ぶベクトル
			if (sts == false) {
				return false;
			}
		}
	}

	return true;
}