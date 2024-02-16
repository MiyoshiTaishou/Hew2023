#pragma once

#include <xaudio2.h>
#include <thread>
#include <mutex>
#include<atomic>
#include "../Component/component.h"

//SE,BGM������R���|�[�l���g
class Audio : public Component
{
private:
	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;

	IXAudio2SourceVoice*	m_SourceVoice{};
	BYTE*					m_SoundData{};

	int						m_Length{};
	int						m_PlayLength{};

	//����
	float m_Volume = 0.0f;	
	std::atomic<bool> m_FadeFinished = true; // �t�F�[�h���I���������ǂ����������t���O
	std::mutex m_UIMutex;
	std::condition_variable m_UICondition;

public:
	static void InitMaster();
	static void UninitMaster();

	using Component::Component;

	void Uninit();

	void Load(const char *FileName);
	void Play(bool Loop = false);
	void PlaySE(bool Loop = false);
	void Stop();

	float GetVolume();
	void SetVolume(float _volume);

	bool GetFade();

	// �Đ����I���������ǂ����𔻒肷�郁�\�b�h
	bool IsSoundPlaying();

	void FadeThread(Audio* audio, float targetVolume, float fadeDuration);

	void FadeVolume(float targetVolume, float fadeDuration);

	//���̃t�F�[�h�̊ԌĂԏ���
	void DrawUI();
};

