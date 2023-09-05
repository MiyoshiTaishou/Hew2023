#include "BoxCollider.h"
#include"gameObject.h"
#include"box.h"
#include"ImGuiManager.h"

using namespace DirectX::SimpleMath;

void BoxCollider::Init()
{	
	//当たり判定の大きさをオブジェクトの大きさに合わせる
	mScale = m_GameObject->GetScale();	
}

void BoxCollider::Update()
{
	//オブジェクトの座標に当たり判定の座標を合わせる
	mHitBox = m_GameObject->GetPosition();
}

void BoxCollider::Draw()
{	
}

bool BoxCollider::HitCheck(BoxCollider other)
{
	float x = mHitBox.x;
	float y = mHitBox.y;
	float z = mHitBox.z;

	float sx = mScale.x;
	float sy = mScale.y;
	float sz = mScale.z;

	float xMax = x + sx / 2;
	float xMin = x - sx / 2;
	float yMax = y + sy / 2;
	float yMin = y - sy / 2;
	float zMax = z + sz / 2;
	float zMin = z - sz / 2;	

	Vector3 vecbox = other.GetHitBox();
	Vector3 vecScale = other.GetScale();

	float vx = vecbox.x;
	float vy = vecbox.y;
	float vz = vecbox.z;

	float svx = vecScale.x;
	float svy = vecScale.y;
	float svz = vecScale.z;

	float xMaxOther = vx + svx / 2;
	float xMinOther = vx - svx / 2;
	float yMaxOther = vy + svy / 2;
	float yMinOther = vy - svy / 2;
	float zMaxOther = vz + svz / 2;
	float zMinOther = vz - svz / 2;	

	bool xOverlap = (xMax >= xMinOther && xMin <= xMaxOther);
	bool yOverlap = (yMax >= yMinOther && yMin <= yMaxOther);
	bool zOverlap = (zMax >= zMinOther && zMin <= zMaxOther);

	if (xOverlap && yOverlap && zOverlap) {		
		return true;
	}

}

DirectX::SimpleMath::Vector3 BoxCollider::GetHitBox()
{
	return mHitBox;
}

DirectX::SimpleMath::Vector3 BoxCollider::GetScale()
{
	return mScale;
}
