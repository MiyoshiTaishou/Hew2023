#pragma once
#include"scene.h"

class Player;
class Camera;

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

	GameObject* obj;

	//名前変更用変数
	char m_bufferField[256] = "test.csv";
	char m_bufferMap[256] = "test.csv";

	Player* m_Player;
	Camera* m_Camera;
};


