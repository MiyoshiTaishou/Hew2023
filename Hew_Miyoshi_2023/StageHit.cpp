#include "StageHit.h"
#include"gameObject.h"
#include"modelRenderer.h"

using namespace DirectX::SimpleMath;

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
PLANEINFO* g_PlaneInfo = nullptr;				// ���ʃ|���S�����
int				g_NumFaces;							// �O�p�`�|���S����


void StageHitInit(GameObject* obj, const char* FileName)
{
	std::vector<VERTEX_3D> vertices;		// ���_�f�[�^
	int indices;			// �C���f�b�N�X�f�[�^

	std::vector<Vector3>vertex;

	vertices = obj->GetComponent<ModelRenderer>()->GetVertex(FileName);
	indices = obj->GetComponent<ModelRenderer>()->GetIndexNum();

	for (auto m : vertices)
		vertex.emplace_back(m.Position);

	CreateStagePlaneInfoAll(vertex, indices);
}

void StageHitExit()
{
	if (g_PlaneInfo != nullptr) {
		delete[] g_PlaneInfo;
	}
}

void CreateStagePlaneInfoAll(std::vector<Vector3>& v, int idx)
{	
	g_NumFaces = idx / 3;

	g_PlaneInfo = new PLANEINFO[g_NumFaces];

	// �ʐ������[�v
	for (int facecnt = 0; facecnt < g_NumFaces; facecnt++) {

		/*g_PlaneInfo[facecnt].p0.x = v[facecnt * 3].x;
		g_PlaneInfo[facecnt].p0.y = v[facecnt * 3].y;
		g_PlaneInfo[facecnt].p0.z = v[facecnt * 3].z;

		g_PlaneInfo[facecnt].p1.x = v[facecnt * 3 + 1].x;
		g_PlaneInfo[facecnt].p1.y = v[facecnt * 3 + 1].y;
		g_PlaneInfo[facecnt].p1.z = v[facecnt * 3 + 1].z;

		g_PlaneInfo[facecnt].p2.x = v[facecnt * 3 + 2].x;
		g_PlaneInfo[facecnt].p2.y = v[facecnt * 3 + 2].y;
		g_PlaneInfo[facecnt].p2.z = v[facecnt * 3 + 2].z;*/

		g_PlaneInfo[facecnt].p0.x = v[facecnt].x;
		g_PlaneInfo[facecnt].p0.y = v[facecnt].y;
		g_PlaneInfo[facecnt].p0.z = v[facecnt].z;

		g_PlaneInfo[facecnt].p1.x = v[facecnt + 1].x;
		g_PlaneInfo[facecnt].p1.y = v[facecnt + 1].y;
		g_PlaneInfo[facecnt].p1.z = v[facecnt + 1].z;

		g_PlaneInfo[facecnt].p2.x = v[facecnt + 2].x;
		g_PlaneInfo[facecnt].p2.y = v[facecnt + 2].y;
		g_PlaneInfo[facecnt].p2.z = v[facecnt + 2].z;

		//���ʂ̕��������쐬����
		CreatePlaneInfo(g_PlaneInfo[facecnt].p0, g_PlaneInfo[facecnt].p1, g_PlaneInfo[facecnt].p2, g_PlaneInfo[facecnt].plane);
	}
}

bool SearchAllSurface(float x, float z, DirectX::SimpleMath::Vector3& ans)
{
	Vector3		DownVector(0, 1, 0);				// �����̕����x�N�g��
	Vector3		CrossPoint;							// ��_
	Vector3		CurrentPosition(x, 0, z);			// ���݈ʒu�i�������Ȃ��j

	bool FindFlag = false;								// �|���S���������������ǂ���
	bool status;

	// �S�|���S���������[�v
	for (int i = 0; i < g_NumFaces; i++) {
		// ���ʂƒ����̌�_�����߂�
		status = LinetoPlaneCross(g_PlaneInfo[i].plane,	//���ʂ̕�����
			CurrentPosition,							//�����̋N�_�i���̌��݈ʒu�j
			DownVector,									//�����̕����x�N�g��
			CrossPoint);								//��_���W
		if (status) {
			// ��_���R�p�`�̓����ɂ��邩�H
			if (CheckInTriangle(g_PlaneInfo[i].p0, g_PlaneInfo[i].p1, g_PlaneInfo[i].p2, CrossPoint)) {
				CurrentPosition.y = CrossPoint.y;
				FindFlag = true;
				break;
			}
		}
	}
	if (FindFlag) {
		ans = CurrentPosition;
		return true;
	}
	else {
		return false;
	}
}

void CreatePlaneInfo(const DirectX::SimpleMath::Vector3& p1, const DirectX::SimpleMath::Vector3& p2, const DirectX::SimpleMath::Vector3& p3, DirectX::SimpleMath::Plane& plane)
{
	Vector3		p1p2;
	Vector3		p2p3;
	Vector3		normal;

	p1p2.x = p2.x - p1.x;
	p1p2.y = p2.y - p1.y;
	p1p2.z = p2.z - p1.z;

	p2p3.x = p3.x - p2.x;
	p2p3.y = p3.y - p2.y;
	p2p3.z = p3.z - p2.z;

	normal.Cross(p1p2, p2p3);

	normal.Normalize(normal);

	plane.x = normal.x;
	plane.y = normal.y;
	plane.z = normal.z;

	plane.w = -(plane.x * p1.x + plane.y * p1.y + plane.z * p1.z);
}

bool LinetoPlaneCross(const DirectX::SimpleMath::Plane& plane, const DirectX::SimpleMath::Vector3& p0, const DirectX::SimpleMath::Vector3& wv, DirectX::SimpleMath::Vector3 ans)
{
	float t = 0;

	Vector3 normal;				// ���ʂ̖@���x�N�g���i���K���ς݁j
	normal.x = plane.x;
	normal.y = plane.y;
	normal.z = plane.z;

	float dot;			// ����
	// ���s�`�F�b�N(���ς��v�Z����)
	dot = normal.Dot(wv);

	float dot2;			// ���q
	dot2 = normal.Dot(p0);	

	t = -(dot2 + plane.w) / dot;

	// �����ɂ������߂鎮������
	ans.x = p0.x + wv.x * t;
	ans.y = p0.y + wv.y * t;
	ans.z = p0.z + wv.z * t;
	return true;
}

bool CheckInTriangle(const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b, const DirectX::SimpleMath::Vector3& c, const DirectX::SimpleMath::Vector3& p)
{
	Vector3	ab, bc, ca;			// �R�ӂ̃x�N�g��
	Vector3	ap, bp, cp;			// �����̓_�Ƃ̃x�N�g��
	Vector3	normal;				// �R�p�`�̖@���x�N�g��
	Vector3	n1, n2, n3;			// �R�ӂƓ����̓_�Ƃ̖@���x�N�g��

	ab.x = b.x - a.x;
	ab.y = b.y - a.y;
	ab.z = b.z - a.z;

	bc.x = c.x - b.x;
	bc.y = c.y - b.y;
	bc.z = c.z - b.z;

	ca.x = a.x - c.x;
	ca.y = a.y - c.y;
	ca.z = a.z - c.z;

	ap.x = p.x - a.x;
	ap.y = p.y - a.y;
	ap.z = p.z - a.z;

	bp.x = p.x - b.x;
	bp.y = p.y - b.y;
	bp.z = p.z - b.z;

	cp.x = p.x - c.x;
	cp.y = p.y - c.y;
	cp.z = p.z - c.z;

	normal.Cross(ab, bc);

	n1.Cross(ab, ap);

	n2.Cross(bc, bp);

	n3.Cross(ca, cp);

	float dot;
	dot = n1.Dot(normal);	
	if (dot < 0) return false;			// �ׂ��p�x���݊p
	dot = n2.Dot(normal);
	if (dot < 0) return false;			// �ׂ��p�x���݊p
	dot = n3.Dot(normal);
	if (dot < 0) return false;			// �ׂ��p�x���݊p

	return true;
}
