#pragma once
#include <cinttypes>
#include "../Scene/scene.h"

// �O���Q��
class Application;

class Manager
{
private:
    static class Scene* m_Scene; // ���݂̃V�[���ւ̃|�C���^

    //�Q�[���V�[��
    static std::string m_FiledName;
    static std::string m_MapName;
    static std::string m_SkyName;

    //BGM���X�g
    static std::vector<std::string> m_BGMList;

    static int m_Count;//�����Ă��̐�
    static int m_CountMax;//�����Ă��̐�

    static bool m_End;

public:
    /**
     * @brief Manager�N���X�̏�����
     * @param ap �A�v���P�[�V�����ւ̃|�C���^
     */
    static void Init(Application* ap);

    /**
     * @brief Manager�N���X�̏I������
     */
    static void Uninit();

    /**
     * @brief Manager�N���X�̍X�V
     * @param d �o�ߎ���
     */
    static void Update(uint64_t d);

    /**
     * @brief Manager�N���X�̕`��
     * @param d �o�ߎ���
     */
    static void Draw(uint64_t d);

    /**
     * @brief ���݂̃V�[�����擾���܂��B
     * @return ���݂̃V�[���ւ̃|�C���^
     */
    static class Scene* GetScene()
    {
        return m_Scene;
    }

    /**
     * @brief �V�����V�[����ݒ肵�܂��B
     * @tparam T �ݒ肷��V�����V�[���̃N���X�^
     */
    template <typename T>
    static void SetScene()
    {
        // ���݂̃V�[�����N���A���ĐV�����V�[����ݒ�
        if (m_Scene)
        {
            m_Scene->UninitBase();
            delete m_Scene;
        }

        m_Scene = new T();
        m_Scene->InitBase();
    }

    //�����Ă��ɐ���ǉ�
    static void AddCount(int _count)
    {
        m_Count += _count;
    }

    static int GetCount()
    {
        return m_Count;
    }

    static int GetCountMax()
    {
        return m_CountMax;
    }

    static std::string GetFiledName()
    {
        return m_FiledName;
    }

    static std::string GetMapName()
    {
        return m_MapName;
    }

    static std::string GetSkyName()
    {
        return m_SkyName;
    }

    static bool GetEnd()
    {
        return m_End;
    }

    static std::vector<std::string> GetBGMList()
    {
        return m_BGMList;
    }

    static void SetCountMax(int _count)
    {
        m_CountMax = _count;
    }

    static void InitCount()
    {
        m_Count = 0;
    }

    static void SetFiledName(std::string _text) 
    {
        m_FiledName = _text;
    }

    static void SetMapName(std::string _text)
    {
        m_MapName = _text;
    }

    static void SetSkyName(std::string _text)
    {
        m_SkyName = _text;
    }

    static void SetEnd(bool _end)
    {
        m_End = _end;
    }  

    static void SetBGMList(std::vector<std::string> _list)
    {
        m_BGMList = _list;
    }
};
