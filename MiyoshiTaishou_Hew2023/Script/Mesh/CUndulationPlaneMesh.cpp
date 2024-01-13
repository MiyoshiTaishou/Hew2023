#include "CUndulationPlaneMesh.h"
#include"Perlinnoise.h"

#include"../ImGui/ImGuiManager.h"
#include <string>
#include <fstream>
#include <sstream>

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

	if (ImGui::Button("Resset"))
	{
		for (size_t i = 0; i < m_vertices.size(); ++i)
		{
			m_vertices[i].Position.y = 0.0f;
		}
	}

	for (size_t i = 0; i < m_vertices.size(); ++i) 
	{
		ImGui::SliderFloat(("Vertex " + std::to_string(i)).c_str(), &m_vertices[i].Position.y, 0, 50);	
		m_vertices[i].Position.y = floor(m_vertices[i].Position.y);
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
			std::istringstream ss(line);
			std::string token;

			// "Vertex" �𖳎����ăJ���}�ōs�𕪊����A2�Ԗڂ̗v�f�� float �ɕϊ����� loadedData �ɒǉ�
			while (std::getline(ss, token, ',')) {
				size_t found = token.find("Vertex");
				if (found != std::string::npos) {
					// "Vertex" ���܂ރg�[�N���͖������Ď��̃g�[�N����
					continue;
				}

				loadedData.push_back(std::stof(token)); // ������� float �ɕϊ����� loadedData �ɒǉ�
			}
		}
		file.close();

		// m_vertices �̍X�V
		if (loadedData.size() == m_vertices.size()) {
			for (size_t i = 0; i < m_vertices.size(); ++i) {
				m_vertices[i].Position.y = loadedData[i];
			}
		}
		else {
			std::cout << "�t�@�C������ǂݎ�����f�[�^�� m_vertices �̗v�f���ƈ�v���܂���B" << std::endl;
		}
	}
	else {
		std::cout << "�t�@�C�����J���܂���ł���: " << filename << std::endl;
	}
}
