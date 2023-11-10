#pragma once
#include"scene.h"

class StageEditor : public Scene
{
public:
	void Init()override;
	void Update()override;
	void Draw()override;

private:
	//オブジェクトの生成
	void CreateObj();

	//オブジェクト値調整関数
	void ObjListManger();

	//リストのオブジェクトのIndex
	int selectedObjectIndex = -1;
};


