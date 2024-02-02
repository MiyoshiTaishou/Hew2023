#pragma once
#include "../Object/gameObject.h"

//客の頭の上に配置する数字を表示するクラス

class BillBoardScore : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	int m_Count;

	float m_Width = 1.0f;
	float m_Height = 1.0f;

	float m_AnimMax = 3.0f;
	float m_AnimMin = 2.0f;

	bool m_UpDown = true;

public:
	void Init();
	void Uninit();
	void Draw();
	void Update();
	void AddCount(int Count) { m_Count += Count; }
	int GetCount() { return m_Count; }
};