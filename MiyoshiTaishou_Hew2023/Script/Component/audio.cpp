#include "../Sysytem/main.h"
#include "audio.h"
#include"../ImGui/ImGuiManager.h"
#include"../Sysytem/manager.h"

#include"../Scene/scene.h"

IXAudio2*				Audio::m_Xaudio = NULL;
IXAudio2MasteringVoice*	Audio::m_MasteringVoice = NULL;

void Audio::InitMaster()
{
	// COM������
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio����
	XAudio2Create(&m_Xaudio, 0);

	// �}�X�^�����O�{�C�X����
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
	// �T�E���h�f�[�^�Ǎ�
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

	// �T�E���h�\�[�X����
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

	// �o�b�t�@�ݒ�
	XAUDIO2_BUFFER bufinfo;

	memset(&bufinfo, 0x00, sizeof(bufinfo));
	bufinfo.AudioBytes = m_Length;
	bufinfo.pAudioData = m_SoundData;
	bufinfo.PlayBegin = 0;
	bufinfo.PlayLength = m_PlayLength;

	// ���[�v�ݒ�
	if (Loop)
	{
		bufinfo.LoopBegin = 0;
		bufinfo.LoopLength = m_PlayLength;
		bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	m_SourceVoice->SubmitSourceBuffer(&bufinfo, NULL);	

	// �Đ�
	m_SourceVoice->Start();

	FadeVolume(1.0f, 3.0f);

}

void Audio::PlaySE(bool Loop)
{
	m_SourceVoice->Stop();
	m_SourceVoice->FlushSourceBuffers();

	// �o�b�t�@�ݒ�
	XAUDIO2_BUFFER bufinfo;

	memset(&bufinfo, 0x00, sizeof(bufinfo));
	bufinfo.AudioBytes = m_Length;
	bufinfo.pAudioData = m_SoundData;
	bufinfo.PlayBegin = 0;
	bufinfo.PlayLength = m_PlayLength;

	// ���[�v�ݒ�
	if (Loop)
	{
		bufinfo.LoopBegin = 0;
		bufinfo.LoopLength = m_PlayLength;
		bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	m_SourceVoice->SubmitSourceBuffer(&bufinfo, NULL);

	// �Đ�
	m_SourceVoice->Start();	
}

void Audio::Stop()
{	
	// �Đ����I���܂őҋ@
	while (IsSoundPlaying())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	// �t�F�[�h�A�E�g
	FadeVolume(0.0f, 3.0f);

	// �t�F�[�h�I����ҋ@
	while (!m_FadeFinished)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	// �Đ���~
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
	// ���݂̍Đ��ʒu���擾
	XAUDIO2_VOICE_STATE state;
	m_SourceVoice->GetState(&state);
	UINT64 currentPosition = state.SamplesPlayed;

	// �Đ��J�n����̌o�ߎ��Ԃ��v�Z
	float elapsedTimeInSeconds = static_cast<float>(currentPosition) / 44100.0f; // ���݂̍Đ��ʒu��b�P�ʂɕϊ�

	// �Ȃ̑��Đ����Ԃ��擾
	float totalTimeInSeconds = static_cast<float>(m_PlayLength) / 44100.0f; // �Ȃ̍Đ����Ԃ�b�P�ʂɕϊ�

	// �Ȃ��I���3�b�O���ǂ����𔻒�
	return totalTimeInSeconds - elapsedTimeInSeconds <= 3.0f;
}

void Audio::FadeThread(Audio* audio, float targetVolume, float fadeDuration)
{	
	// �t�F�[�h�����̎���
	float startVolume = audio->GetVolume();
	float deltaVolume = (targetVolume - startVolume) / fadeDuration;
	float currentVolume = startVolume;
	while (currentVolume != targetVolume) 
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); // �t�F�[�h�����̊Ԋu
		currentVolume += deltaVolume * 0.01f; // 10ms���Ƃɉ��ʂ𒲐�
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
		fadeThread.detach(); // ���C���X���b�h����؂藣��			
	}
}

void Audio::DrawUI()
{
	Scene* scene = Manager::GetScene();

	scene->GetLoadUI()->DrawBase(DirectX::SimpleMath::Matrix::Identity);
	scene->GetLoadUI()->UpdateBase();
	
}
