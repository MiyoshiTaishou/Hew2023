#pragma once


#include "../Object/gameObject.h"

class BillBoardScore : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	int m_Count;

	float m_Width = 1.0f;
	float m_Height = 1.0f;

public:
	void Init();
	void Uninit();
	void Draw();
	void Update();
	void AddCount(int Count) { m_Count += Count; }
};