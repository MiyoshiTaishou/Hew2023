#include "CUndulationPlaneMesh.h"
#include"Perlinnoise.h"

#include"../ImGui/ImGuiManager.h"
#include <string>
#include <fstream>

void CUndulationPlaneMesh::MakeUndulation(float min, float max)
{
	std::mt19937 mt;
	std::uniform_real_distribution<float> dist(min, max);

	for (auto& v : m_vertices) {
		v.Position.y = dist(mt);
	}
}

void CUndulationPlaneMesh::MakeUndulationPerlinnoise(float max, double octave, double persistence)
{
	PerlinNoise perlin;
	for (auto& v : m_vertices) {

		//		double d = perlin.noise(
		//			v.Position.x*0.1,
		//			0,
		//			v.Position.z);

		double d = perlin.octaveNoise(
			v.Position.x,
			0,
			v.Position.z,
			octave,
			persistence);

		v.Position.y = d * max;
	}
}

void CUndulationPlaneMesh::MakeUndulationSelf()
{
	ImGui::Begin("FieldMake");
	for (size_t i = 0; i < m_vertices.size(); ++i) 
	{
		ImGui::SliderFloat(("Vertex " + std::to_string(i)).c_str(), &m_vertices[i].Position.y, 0, 100);		
	}
	ImGui::End();
}

void CUndulationPlaneMesh::SaveUndulation(const std::string& filename)
{
	std::ofstream file(filename);

	if (file.is_open()) {
		for (size_t i = 0; i < m_vertices.size(); ++i) {
			file << "Vertex " << i << ", " << m_vertices[i].Position.y << "\n";
		}
		file.close();
		// File saved successfully
	}
	else {
		// Unable to open the file
	}
}

void CUndulationPlaneMesh::LoadUndulation(const std::string& filename)
{
	std::ifstream file(filename);

	std::vector<float> loadedData;

	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			// �����Ńt�@�C������ǂݍ��񂾃f�[�^����͂��A�K�v�ȏ������s��
			// ���̗�ł́A"," �ŕ������� Position.y �̒l���擾�� loadedData �ɒǉ�����
			size_t pos = line.find(",");
			if (pos != std::string::npos) {
				std::string value = line.substr(pos + 2); // ", " �̌��̕�������擾
				loadedData.push_back(std::stof(value)); // ������� float �ɕϊ����� loadedData �ɒǉ�
			}
		}
		file.close();

		for (size_t i = 0; i < m_vertices.size(); ++i)
		{
			m_vertices[i].Position.y = loadedData[i];
		}
	}
	else {
		std::cout << "Unable to open the file: " << filename << std::endl;
	}
}
