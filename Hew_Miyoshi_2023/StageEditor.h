#pragma once
#include "scene.h"

//列挙型でクラスの種類を管理
enum CLASS
{
	BOX,
	ENEMY,
	NONE,
};

struct InfoObjData
{
	CLASS ClassKind;
	DirectX::SimpleMath::Vector3 pos;
	DirectX::SimpleMath::Vector3 scale;
	DirectX::SimpleMath::Vector3 rot;
};

class StageEditor : public Scene
{
public:
	void Init()override;
	void Update()override;
	void Draw()override;

	void SavepositionToFile(const std::string& filename);
	void LoadpositionToFile(const std::string& filename);
	void CreateObject();

	void AddToHistory();
	void Undo();
	void Redo();
private:
	//std::vector<InfoObjData> position;

	// 履歴管理用のコンテナ
	std::array<std::list<InfoObjData>, 4> history;
	std::vector<InfoObjData> position;
	std::vector<GameObject*> objList;

	int historyIndex = 0;
};

