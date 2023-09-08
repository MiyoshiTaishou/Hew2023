/**
 * @file Polygon2D.h
 * @brief 2Dポリゴンを表示する
 * @author 三好大翔
 */
#pragma once

#include	<d3d11.h>
#include	<SimpleMath.h>
#include	"gameObject.h"

class Polygon2D : public GameObject
{
private:

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};