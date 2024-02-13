#pragma once


#include "../Object/gameObject.h"

class Score : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	int m_Count;

	int m_Interval = 60.0f;

public:
	void Init();
	void Init(int x, int y, int Width, int Height);
	void Uninit();
	void Draw();	
	void AddCount(int Count) { m_Count += Count; }
	int GetCount() { return m_Count; }
};