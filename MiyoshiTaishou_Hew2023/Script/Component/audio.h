#pragma once

#include <xaudio2.h>
#include <thread>
#include <mutex>
#include<atomic>
#include "../Component/component.h"

//SE,BGMを入れるコンポーネント
class Audio : public Component
{
private:
	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;

	IXAudio2SourceVoice*	m_SourceVoice{};
	BYTE*					m_SoundData{};

	int						m_Length{};
	int						m_PlayLength{};

	//音量
	float m_Volume = 0.0f;	
	std::atomic<bool> m_FadeFinished = true; // フェードが終了したかどうかを示すフラグ
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

	// 再生が終了したかどうかを判定するメソッド
	bool IsSoundPlaying();

	void FadeThread(Audio* audio, float targetVolume, float fadeDuration);

	void FadeVolume(float targetVolume, float fadeDuration);

	//音のフェードの間呼ぶ処理
	void DrawUI();
};

