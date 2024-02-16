#include "../Sysytem/main.h"
#include "audio.h"
#include"../ImGui/ImGuiManager.h"
#include"../Sysytem/manager.h"

#include"../Scene/scene.h"

IXAudio2*				Audio::m_Xaudio = NULL;
IXAudio2MasteringVoice*	Audio::m_MasteringVoice = NULL;

void Audio::InitMaster()
{
	// COM初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio生成
	XAudio2Create(&m_Xaudio, 0);

	// マスタリングボイス生成
	m_Xaudio->CreateMasteringVoice(&m_MasteringVoice);
}


void Audio::UninitMaster()
{
	m_MasteringVoice->DestroyVoice();
	m_Xaudio->Release();
	CoUninitialize();
}

void Audio::Load(const char *FileName)
{
	// サウンドデータ読込
	WAVEFORMATEX wfx = { 0 };

	{
		HMMIO hmmio = NULL;
		MMIOINFO mmioinfo = { 0 };
		MMCKINFO riffchunkinfo = { 0 };
		MMCKINFO datachunkinfo = { 0 };
		MMCKINFO mmckinfo = { 0 };
		UINT32 buflen;
		LONG readlen;


		hmmio = mmioOpen((LPSTR)FileName, &mmioinfo, MMIO_READ);
		assert(hmmio);

		riffchunkinfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(hmmio, &riffchunkinfo, NULL, MMIO_FINDRIFF);

		mmckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(hmmio, &mmckinfo, &riffchunkinfo, MMIO_FINDCHUNK);

		if (mmckinfo.cksize >= sizeof(WAVEFORMATEX))
		{
			mmioRead(hmmio, (HPSTR)&wfx, sizeof(wfx));
		}
		else
		{
			PCMWAVEFORMAT pcmwf = { 0 };
			mmioRead(hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
			memset(&wfx, 0x00, sizeof(wfx));
			memcpy(&wfx, &pcmwf, sizeof(pcmwf));
			wfx.cbSize = 0;
		}
		mmioAscend(hmmio, &mmckinfo, 0);

		datachunkinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(hmmio, &datachunkinfo, &riffchunkinfo, MMIO_FINDCHUNK);

		buflen = datachunkinfo.cksize;
		m_SoundData = new unsigned char[buflen];
		readlen = mmioRead(hmmio, (HPSTR)m_SoundData, buflen);

		m_Length = readlen;
		m_PlayLength = readlen / wfx.nBlockAlign;

		mmioClose(hmmio, 0);
	}

	// サウンドソース生成
	m_Xaudio->CreateSourceVoice(&m_SourceVoice, &wfx);
	assert(m_SourceVoice);
}

void Audio::Uninit()
{
	if (m_SourceVoice != nullptr)
	{
		m_SourceVoice->Stop();
		m_SourceVoice->DestroyVoice();
	}

	delete[] m_SoundData;
}

void Audio::Play(bool Loop)
{
	m_SourceVoice->Stop();
	m_SourceVoice->FlushSourceBuffers();

	// バッファ設定
	XAUDIO2_BUFFER bufinfo;

	memset(&bufinfo, 0x00, sizeof(bufinfo));
	bufinfo.AudioBytes = m_Length;
	bufinfo.pAudioData = m_SoundData;
	bufinfo.PlayBegin = 0;
	bufinfo.PlayLength = m_PlayLength;

	// ループ設定
	if (Loop)
	{
		bufinfo.LoopBegin = 0;
		bufinfo.LoopLength = m_PlayLength;
		bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	m_SourceVoice->SubmitSourceBuffer(&bufinfo, NULL);	

	// 再生
	m_SourceVoice->Start();

	FadeVolume(1.0f, 3.0f);

}

void Audio::PlaySE(bool Loop)
{
	m_SourceVoice->Stop();
	m_SourceVoice->FlushSourceBuffers();

	// バッファ設定
	XAUDIO2_BUFFER bufinfo;

	memset(&bufinfo, 0x00, sizeof(bufinfo));
	bufinfo.AudioBytes = m_Length;
	bufinfo.pAudioData = m_SoundData;
	bufinfo.PlayBegin = 0;
	bufinfo.PlayLength = m_PlayLength;

	// ループ設定
	if (Loop)
	{
		bufinfo.LoopBegin = 0;
		bufinfo.LoopLength = m_PlayLength;
		bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	m_SourceVoice->SubmitSourceBuffer(&bufinfo, NULL);

	// 再生
	m_SourceVoice->Start();	
}

void Audio::Stop()
{	
	// 再生が終わるまで待機
	while (IsSoundPlaying())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	// フェードアウト
	FadeVolume(0.0f, 3.0f);

	// フェード終了を待機
	while (!m_FadeFinished)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	// 再生停止
	m_SourceVoice->Stop();
	m_SourceVoice->FlushSourceBuffers();
}

float Audio::GetVolume()
{
	return m_Volume;
}

void Audio::SetVolume(float _volume)
{
	m_Volume = _volume;
	m_SourceVoice->SetVolume(m_Volume);
}

bool Audio::GetFade()
{
	return m_FadeFinished;
}

bool Audio::IsSoundPlaying()
{
	// 現在の再生位置を取得
	XAUDIO2_VOICE_STATE state;
	m_SourceVoice->GetState(&state);
	UINT64 currentPosition = state.SamplesPlayed;

	// 再生開始からの経過時間を計算
	float elapsedTimeInSeconds = static_cast<float>(currentPosition) / 44100.0f; // 現在の再生位置を秒単位に変換

	// 曲の総再生時間を取得
	float totalTimeInSeconds = static_cast<float>(m_PlayLength) / 44100.0f; // 曲の再生時間を秒単位に変換

	// 曲が終わる3秒前かどうかを判定
	return totalTimeInSeconds - elapsedTimeInSeconds <= 3.0f;
}

void Audio::FadeThread(Audio* audio, float targetVolume, float fadeDuration)
{	
	// フェード処理の実装
	float startVolume = audio->GetVolume();
	float deltaVolume = (targetVolume - startVolume) / fadeDuration;
	float currentVolume = startVolume;
	while (currentVolume != targetVolume) 
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); // フェード処理の間隔
		currentVolume += deltaVolume * 0.01f; // 10msごとに音量を調整
		if ((deltaVolume > 0 && currentVolume >= targetVolume) || (deltaVolume < 0 && currentVolume <= targetVolume)) 
		{
			currentVolume = targetVolume;
		}
		audio->SetVolume(currentVolume);		
	}	
	m_FadeFinished.store(true);	
}


void Audio::FadeVolume(float targetVolume, float fadeDuration)
{
	if (m_FadeFinished)
	{		
		m_FadeFinished.store(false);
	
		std::thread fadeThread(&Audio::FadeThread, this, this, targetVolume, fadeDuration);
		fadeThread.detach(); // メインスレッドから切り離す			
	}
}

void Audio::DrawUI()
{
	Scene* scene = Manager::GetScene();

	scene->GetLoadUI()->DrawBase(DirectX::SimpleMath::Matrix::Identity);
	scene->GetLoadUI()->UpdateBase();
	
}
